#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T10:02:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UpgradeTool
TEMPLATE = app

CONFIG += debug_and_release warn_on qt thread
    CONFIG(debug, debug|release) {
    DESTDIR = ../bin
    MOC_DIR      = ./Debug/moc
    OBJECTS_DIR  = ./Debug/obj
    LIBS += -L"../bin"

} else {
    DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
    DEFINES += NDEBUG
    DESTDIR = ../bin
    MOC_DIR      = ./Release/moc
    OBJECTS_DIR  = ./Release/obj
    LIBS += -L"../bin"

}

DEPENDPATH += .
INCLUDEPATH += ../bin
INCLUDEPATH += ./
INCLUDEPATH += ./Common

win32: {
        DEFINES += WIN32
        #DEFINES -= UNICODE
        LIBS += -lws2_32 -lOle32
}

RESOURCES += HTDEMO.qrc
RC_FILE = HTDEMO.rc

SOURCES += ./main.cpp\
    ./adb_tool.cpp \
  ./Common/widgetconfig.cpp \
./Common/mainapp.cpp \
    ./Common/appconfig.cpp \
    ./Common/SetDebugNew.cpp \
 ./Common/CheckTime.cpp \
    ./Common/LanguageSrc.cpp \
    ./Common/maininit.cpp  \
 ./Common/widgetconfig.cpp \
        ./Common/Lock.cpp \
 ./Common/BuzzerSpeakerCtrl.cpp \
    softconfigdlg.cpp \
    MessageBox.cpp

HEADERS  += ./upgrade_tool.pro \
    ./adb_tool.h \
./Common/Singleton.h \
    ./Common/mainapp.h \
    ./Common/appconfig.h \
./Common/SetDebugNew.h \
    ./Common/CheckTime.h\
    ./Common/LanguageSrc.h \
    ./Common/AppPath.h \
    ./Common/maininit.h \
  ./Common/widgetconfig.h \
    ./Common/Lock.h \
./Common/BuzzerSpeakerCtrl.h \
    softconfigdlg.h \
    MessageBox.h

FORMS    += ./adb_tool.ui \
    softconfigdlg.ui



