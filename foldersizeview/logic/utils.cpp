#include "utils.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include "hostosinfo.h"
#include <QDebug>

QString Utils::getContentFromFile(const QString &filePath)
{
    QFile f(filePath);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << f.errorString();
        return "";
    }
    QTextStream in(&f);
    QString content = in.readAll();
    return content;
}

void Utils::showInGraphicalShell(const QString &pathIn)
{
    const QFileInfo fileInfo(pathIn);
    // Mac, Windows support folder or file.
    if (HostOsInfo::isWindowsHost()) {
//        const FileName explorer = Environment::systemEnvironment().searchInPath(QLatin1String("explorer.exe"));
//        const QString explorer = "C:\\Windows\\System\\explorer.exe";
//        if (explorer.isEmpty()) {
//            return;
//        }
        QStringList param;
        if (!fileInfo.isDir())
            param += QLatin1String("/select,");
        param += QDir::toNativeSeparators(fileInfo.canonicalFilePath());
        QProcess::startDetached("explorer", param);
    } else if (HostOsInfo::isMacHost()) {
        QStringList scriptArgs;
        scriptArgs << QLatin1String("-e")
                   << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
                                         .arg(fileInfo.canonicalFilePath());
        QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
        scriptArgs.clear();
        scriptArgs << QLatin1String("-e")
                   << QLatin1String("tell application \"Finder\" to activate");
        QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
    } else {
//        // we cannot select a file here, because no file browser really supports it...
//        const QString folder = fileInfo.isDir() ? fileInfo.absoluteFilePath() : fileInfo.filePath();
//        const QString app = UnixUtils::fileBrowser(ICore::settings());
//        QProcess browserProc;
//        const QString browserArgs = UnixUtils::substituteFileBrowserParameters(app, folder);
//        bool success = browserProc.startDetached(browserArgs);
//        const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
//        success = success && error.isEmpty();
//        if (!success)
//            showGraphicalShellError(parent, app, error);
    }
}
