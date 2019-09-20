#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QWidget>

class Utils
{
public:

    static QString getContentFromFile(const QString &filePath);
    static void showInGraphicalShell(const QString &pathIn);

};

#endif // UTILS_H
