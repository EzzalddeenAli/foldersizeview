#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include <QObject>

class HtmlGenerator : public QObject
{
    Q_OBJECT
public:
    explicit HtmlGenerator(QObject *parent = nullptr);

    void enableSunburstMode(bool enable) { mSunburstMode = enable;}

    bool generate(const QString & data);

    const QString & getResultHtml() const { return mResultHtml; }

signals:

public slots:

private:

    QString getContentFromFile(const QString & filePath);

private:
    QString mResultHtml;
    bool mSunburstMode = false;
};

#endif // HTMLGENERATOR_H
