#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <stack>
#include "counter.h"

#include "../utils/json.hpp"
#include <tuple>

class DirParser : public QObject
{
    Q_OBJECT
public:
    explicit DirParser(QObject *parent = nullptr);

    void enableGroupByFileExtension(bool enable) { mGroupByFileExtension = enable;}

    void startParseDirectory(const QString& dirPath);

    const QString & getResultString() const { return mResultString;}

signals:


public slots:

private:
    void parseGroupByFolder(const QString & currentDir, nlohmann::json & currentJsonArray);

    void parseGroupByFileExtension(const QString &rootDir, nlohmann::json &rootJsonArray);

private:
    Counter mCounter;
    QString mRootDir;
    QString mResultString;
    bool mGroupByFileExtension = false;
};

#endif // HANDLER_H
