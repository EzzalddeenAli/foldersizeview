#-------------------------------------------------
#
# Project created by QtCreator 2019-07-05T00:45:06
#
#-------------------------------------------------

QT       += core gui widgets webenginewidgets


TARGET = FolderSizeView
TEMPLATE = app

ICON = foldersizeview.icns
win32 {
RC_ICONS = foldersizeview.ico
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        ganalytics.cpp \
        logic/config.cpp \
        logic/counter.cpp \
        logic/dirparser.cpp \
        logic/hostosinfo.cpp \
        logic/htmlgenerator.cpp \
        logic/utils.cpp \
        main.cpp \
        mainwindow.cpp \
        svapp.cpp \
        webview.cpp \
        webviewobject.cpp

HEADERS += \
        ganalytics.h \
        logic/config.h \
        logic/counter.h \
        logic/dirparser.h \
        logic/hostosinfo.h \
        logic/htmlgenerator.h \
        logic/utils.h \
        mainwindow.h \
        svapp.h \
        utils/json.hpp \
        utils/tinyformat.h \
        webview.h \
        webviewobject.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    foldersizeview.qrc
