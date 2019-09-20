#ifndef SVAPP_H
#define SVAPP_H

#include <QObject>
#include "ganalytics.h"

class SVApp : public QObject
{
    Q_OBJECT
public:
    explicit SVApp(QObject *parent = nullptr);

    void trackAppEvent(const QString &action);

signals:

public slots:

private slots:
    void onAnalyticsIsSendingChanged(bool sending);
private:
    std::shared_ptr<GAnalytics> _tracker;

};


extern SVApp *app;

#endif // SVAPP_H
