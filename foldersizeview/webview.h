#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWidget>
#include <QtWebEngineWidgets>

namespace Ui {
class WebView;
}

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = nullptr);
    ~WebView();

    void dropEvent(QDropEvent* event);
    void contextMenuEvent(QContextMenuEvent *event);

    void setRevealPath(const QString & path) { mRevealPath = path; }

signals:
    void signalDropFolderEvent(QString dirPath);

private:
    QAction *mRevealInFinderAction = nullptr;

    QString mRevealPath;
};

#endif // WEBVIEW_H
