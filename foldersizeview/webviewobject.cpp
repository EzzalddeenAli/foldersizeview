#include "webviewobject.h"

WebViewObject::WebViewObject(QObject *parent) : QObject(parent)
{

}

void WebViewObject::JSSendMessage(QString strParameter)
{
    emit SigReceivedMessageFromJS(strParameter);
}
