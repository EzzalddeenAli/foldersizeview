#include "webview.h"
#include <QDebug>
#include <QDir>
#include "logic/utils.h"
#include "logic/hostosinfo.h"

WebView::WebView(QWidget *parent) :
    QWebEngineView(parent)
{

}

WebView::~WebView()
{
}

void WebView::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        if (urlList.length() == 0) {
            return;
        }
        if (urlList.length() > 1) {
            return;
        }

        QString dirPath = urlList.first().toLocalFile();

        qDebug() << dirPath;

        QDir dir(dirPath);
        if (!dir.exists()) {
            return;
        }

        emit signalDropFolderEvent(dirPath);
    }
}

void WebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = page()->createStandardContextMenu();
    menu->clear();
    menu->insertAction(nullptr, page()->action(QWebEnginePage::Reload));

    if (!mRevealPath.isEmpty()) {
        if (mRevealInFinderAction == nullptr) {

            QString actionName;
            if (HostOsInfo::isMacHost()) {
                actionName = "Reveal in Finder";
            } else {
                actionName = "Show in Explorer";
            }

            mRevealInFinderAction = new QAction(actionName);
            mRevealInFinderAction->setIcon(QIcon(":/res/reveal"));
            connect(mRevealInFinderAction,&QAction::triggered,this,[&](bool) {

                Utils::showInGraphicalShell(mRevealPath);

            });
        }
        menu->insertAction(nullptr, mRevealInFinderAction);
    }

    menu->popup(event->globalPos());
}
