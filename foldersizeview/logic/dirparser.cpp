#include "dirparser.h"
#include <unordered_map>
#include <list>
#include <stack>

using namespace nlohmann;

DirParser::DirParser(QObject *parent) : QObject(parent)
{

}

void DirParser::startParseDirectory(const QString &dirPath)
{
    mRootDir = dirPath;

    json result = json::array({});

    if (mGroupByFileExtension) {
        parseGroupByFileExtension(mRootDir,result);
    } else {
        parseGroupByFolder(mRootDir,result);
    }

    mResultString = QString::fromStdString(result.dump(4));

//#ifdef QT_DEBUG
//    printf("%s\n",mResultString.toStdString().c_str());
//#endif
}

void DirParser::parseGroupByFolder(const QString &currentDir, json &currentJsonArray)
{
    QDir dir(currentDir);
    if (!dir.exists()) {
        return;
    }
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);

    QFileInfoList itemList = dir.entryInfoList();
    for (QFileInfo & info : itemList) {
        if (info.fileName() == "." || info.fileName() == "..") {
            continue;
        }
        mCounter.countFileInfo(info);

        QString relativeFilePath = info.absoluteFilePath().replace(mRootDir,"");
        if (!relativeFilePath.startsWith(QDir::separator())) {
            relativeFilePath.insert(0,QDir::separator());
        }

        json jsonItem = json::object();
        jsonItem["name"] = info.fileName().toStdString();
        jsonItem["path"] = relativeFilePath.toStdString();

        if (info.isDir()) {
            // go into
            json children = json::array({});
            parseGroupByFolder(info.absoluteFilePath(),children);
            jsonItem["children"] = children;
        } else {
            jsonItem["value"] = info.size();
        }
        currentJsonArray.push_back(jsonItem);
    }
}

void DirParser::parseGroupByFileExtension(const QString &rootDir, json &rootJsonArray)
{
    std::unordered_map<std::string,std::shared_ptr<std::list<QFileInfo>>> maps; // file extension - list of file info

    std::stack<QString> dirStack;
    dirStack.push(rootDir);

    while (!dirStack.empty()) {
        QString currentDir = dirStack.top();
        dirStack.pop();

        QDir dir(currentDir);
        if (!dir.exists()) {
            continue;
        }
        dir.setFilter(QDir::Dirs | QDir::Files);
        dir.setSorting(QDir::DirsFirst);

        QFileInfoList itemList = dir.entryInfoList();
        for (QFileInfo & info : itemList) {
            if (info.fileName() == "." || info.fileName() == "..") {
                continue;
            }
            mCounter.countFileInfo(info);

            if (info.isDir()) {
                // go into
                dirStack.push(info.absoluteFilePath());
                continue;
            }

            auto ext = info.completeSuffix().toStdString();
            if (ext.empty()) {
                ext = "/NoFileExtension/";
            }

            if (maps.find(ext) == maps.end()) {
                maps[ext] = std::make_shared<std::list<QFileInfo>>();
            }
            std::shared_ptr<std::list<QFileInfo>> files = maps[ext];

            files->push_back(info);
        }
    }

    for (auto & item : maps) {
        auto & ext = item.first;
        auto & files = item.second;

        json children = json::array({});
        for (auto & info : *files) {

            QString relativeFilePath = info.absoluteFilePath().replace(mRootDir,"");
            if (!relativeFilePath.startsWith(QDir::separator())) {
                relativeFilePath.insert(0,QDir::separator());
            }

            json jsonItem = json::object();
            jsonItem["name"] = info.fileName().toStdString();
            jsonItem["path"] = relativeFilePath.toStdString();
            jsonItem["value"] = info.size();

            children.push_back(jsonItem);
        }

        json jsonItem = json::object();
        jsonItem["name"] = ext;
        jsonItem["path"] = "/";
        jsonItem["children"] = children;

        rootJsonArray.push_back(jsonItem);
    }
}
