#include "htmlgenerator.h"
#include <QFile>
#include <QTextStream>
#include "utils.h"
#include <QDebug>

HtmlGenerator::HtmlGenerator(QObject *parent) : QObject(parent)
{

}

bool HtmlGenerator::generate(const QString &data)
{
    // read template
    QString content;

    if (mSunburstMode) {
        content = Utils::getContentFromFile(":/template/sunburst");
    } else {
        content = Utils::getContentFromFile(":/template/treemap");
    }

    QString core = Utils::getContentFromFile(":/res/echarts");

//    qDebug() << " core = " << core;

    // replace
    content.replace("{{{data}}}",data);
    content.replace("{{{core}}}",core);

//#ifdef QT_DEBUG
//    qDebug() << "after replace core" << content;
//#endif
    mResultHtml = content;
    return true;
}
