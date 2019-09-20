#ifndef WEBVIEWOBJECT_H
#define WEBVIEWOBJECT_H

#include <QObject>

class WebViewObject : public QObject
{
    Q_OBJECT
public:
    explicit WebViewObject(QObject *parent = nullptr);


    Q_INVOKABLE void JSSendMessage(QString strParameter);       //Called by JS: Send message to Qt

signals:
    void SigReceivedMessageFromJS(QString strParameter);          //Receive message from Web

public slots:
};

#endif // WEBVIEWOBJECT_H
