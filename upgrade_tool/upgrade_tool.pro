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

LIBS += -lWIRELESSRFIDAPI

DEPENDPATH += .
INCLUDEPATH += ../bin
INCLUDEPATH += ./

win32: {
        DEFINES += WIN32
        #DEFINES -= UNICODE
        LIBS += -lws2_32 -lOle32
}

RESOURCES += adb_tool.qrc

SOURCES += ./main.cpp\
    ./adb_tool.cpp
    
HEADERS  += ./upgrade_tool.pro \
    ./adb_tool.h

FORMS    += ./adb_tool.ui



