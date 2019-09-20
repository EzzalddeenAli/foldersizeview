#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "svapp.h"
#include "logic/config.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(foldersizeview);

    QApplication a(argc, argv);
    a.setApplicationName("FolderSizeView");
    a.setOrganizationName("everettjf");
    a.setOrganizationDomain("foldersizeview.github.io");
    a.setApplicationVersion(kAppVersion);
    a.setWindowIcon(QIcon(":foldersizeview.icns"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    SVApp s;
    app = &s;

    MainWindow w;
    w.show();

    return a.exec();
}
