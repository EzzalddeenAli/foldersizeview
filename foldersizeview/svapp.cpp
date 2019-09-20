#include "svapp.h"

SVApp *app;


SVApp::SVApp(QObject *parent) : QObject(parent)
{
    _tracker = std::make_shared<GAnalytics>("UA-139398409-7");
    QObject::connect(_tracker.get(), SIGNAL(isSendingChanged(bool)), this, SLOT(onAnalyticsIsSendingChanged(bool)));

    _tracker->setSendInterval(5 * 1000);
    trackAppEvent("app-start");
}

void SVApp::onAnalyticsIsSendingChanged(bool sending)
{
    if (sending){
        return;
    }

    printf("analytics sent\n");
}

void SVApp::trackAppEvent(const QString &action)
{
    if(!_tracker){
        return;
    }
    _tracker->sendEvent("app",action);
}
