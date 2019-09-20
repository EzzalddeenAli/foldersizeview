#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic/dirparser.h"
#include "logic/htmlgenerator.h"
#include "svapp.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDesktopServices>
#include "logic/utils.h"
#include "logic/config.h"
#include "webviewobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionGroup_by_file_extension->setChecked(Config::instance().isEnableGroupByFileExtension());
    ui->actionSunburst_Mode->setChecked(Config::instance().isEnableSunburstMode());

    QString indexContent = Utils::getContentFromFile(":/res/index");
    ui->webview->setHtml(indexContent);

    connect(ui->webview,SIGNAL(signalDropFolderEvent(QString)),this,SLOT(slotDropFolderEvent(QString)));

    QWebChannel *webChannel = new QWebChannel(ui->webview->page());
    WebViewObject *apiObject = new WebViewObject(this);
    webChannel->registerObject("apiObject",apiObject);
    ui->webview->page()->setWebChannel(webChannel);

    connect(apiObject, &WebViewObject::SigReceivedMessageFromJS, this, [&](QString str){
//        qDebug() << mCurrentFolderPath;
//        qDebug() << str;

        if (str.isEmpty()) {
            ui->webview->setRevealPath("");
        } else {
            QString path = mCurrentFolderPath + str.right(str.length()-1);
            ui->webview->setRevealPath(path);
        }
    });

//#ifdef QT_DEBUG
//    showFolder("/Users/everettjf/Downloads/Wechat.app");
//#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFolder(const QString &dirPath)
{
    mCurrentFolderPath = dirPath;

    refreshFolder();
}

void MainWindow::refreshFolder()
{
    if (mCurrentFolderPath.isEmpty()) {
        return;
    }

    bool enableGroupByFileExtension = Config::instance().isEnableGroupByFileExtension();
    bool enableSunburstMode = Config::instance().isEnableSunburstMode();


    DirParser parser;
    parser.enableGroupByFileExtension(enableGroupByFileExtension);
    parser.startParseDirectory(mCurrentFolderPath);
    QString data = parser.getResultString();

    HtmlGenerator generator;
    generator.enableSunburstMode(enableSunburstMode);
    if(!generator.generate(data)) {
        return;
    }

    QString html = generator.getResultHtml();
    ui->webview->setHtml(html);
}

void MainWindow::on_actionOpen_triggered()
{
    app->trackAppEvent(QString("open"));

    const QString desktopFolder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);


    QString dirPath = QFileDialog::getExistingDirectory(this, "Open Folder",
                                                desktopFolder,
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if (dirPath.isEmpty()) {
        return;
    }

    showFolder(dirPath);

}

void MainWindow::on_actionExport_triggered()
{
    app->trackAppEvent(QString("export"));
    const QString desktopFolder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString defaultFileName = desktopFolder;
    defaultFileName.append(QDir::separator());
    defaultFileName.append("FolderSizeView.html");

    QString fileName = QFileDialog::getSaveFileName(this,"Export Html",defaultFileName,"Html (*.html)");
    qDebug() << fileName;

    if (fileName.isEmpty()){
        return;
    }
    ui->webview->page()->toHtml([this,fileName](const QString & content) {

        QString fixedContent = content;
        // !!! trick
        fixedContent.replace("<script type=\"text/javascript\" src=\"qrc:///res/webchannel\"></script>","");
        fixedContent.replace("new QWebChannel(qt.webChannelTransport,function(channel){apiObject=channel.objects.apiObject;});","");

        QFile file(fileName);
        if (file.exists()) {
            file.remove();
        }
        if (!file.open(QIODevice::ReadWrite)) {
            QMessageBox::critical(this,"Error","Can not open file for write");
            return;
        }

        QTextStream out(&file);
        out << fixedContent;

        file.close();
    });
}

void MainWindow::on_actionAbout_triggered()
{
    app->trackAppEvent(QString("about"));

    QString info = QString("FolderSizeView\n\n"
                           "v%1\n\n"
                           "FolderSizeView is written by everettjf\n\n"
                           "Copyright © 2019 everettjf. All rights reserved."
                           ).arg(kAppVersion);

    QMessageBox::information(this,"About",info);
}

void MainWindow::on_actionReload_triggered()
{
    ui->webview->reload();
}

void MainWindow::slotDropFolderEvent(QString dirPath)
{
    app->trackAppEvent(QString("drop_folder"));

    showFolder(dirPath);
}

void MainWindow::on_actionFollow_Wechat_triggered()
{
    app->trackAppEvent(QString("follow_wechat"));
    QDesktopServices::openUrl(QUrl("https://everettjf.github.io/bukuzao"));
}

void MainWindow::on_actionBuy_me_a_coffee_triggered()
{
    app->trackAppEvent(QString("export"));
    QDesktopServices::openUrl(QUrl("https://everettjf.github.io/donate"));

}

void MainWindow::on_actionBuy_my_products_triggered()
{
    app->trackAppEvent(QString("buy_my_product"));
    QDesktopServices::openUrl(QUrl("https://everettjf.github.io/products"));

}

void MainWindow::on_actionStar_my_projects_triggered()
{
    app->trackAppEvent(QString("star_my_projects"));
    QDesktopServices::openUrl(QUrl("https://github.com/everettjf"));

}

void MainWindow::on_actionFeedback_triggered()
{
    app->trackAppEvent(QString("feedback"));
    QDesktopServices::openUrl(QUrl("https://github.com/foldersizeview/foldersizeview.github.io/issues"));

}

void MainWindow::on_actionReleases_triggered()
{
    app->trackAppEvent(QString("releases"));
    QDesktopServices::openUrl(QUrl("https://github.com/foldersizeview/foldersizeview.github.io/releases"));
}

void MainWindow::on_actionContact_Me_triggered()
{
    app->trackAppEvent(QString("contactme"));
    QDesktopServices::openUrl(QUrl("mailto:everettjf@live.com?subject=FolderSizeView", QUrl::TolerantMode));
}

void MainWindow::on_actionFollow_Weibo_triggered()
{
    app->trackAppEvent(QString("followweibo"));
    QDesktopServices::openUrl(QUrl("https://weibo.com/everettjf"));
}

void MainWindow::on_actionGroup_by_file_extension_triggered(bool checked)
{
    app->trackAppEvent(QString("group_by_file_extension"));
    Config::instance().enableGroupByFileExtension(checked);

    refreshFolder();
}

void MainWindow::on_actionSunburst_Mode_triggered(bool checked)
{
    app->trackAppEvent(QString("sunburst_mode"));
    Config::instance().enableSunburstMode(checked);

    refreshFolder();
}
