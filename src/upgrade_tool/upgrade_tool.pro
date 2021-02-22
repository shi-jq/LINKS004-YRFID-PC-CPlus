QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = UpgradeTool

INCLUDEPATH += . \
               ../../platform/

DEFINES += RFIDAPI_EXPORTS
win32{
    QMAKE_CXXFLAGS -= -Zc:strictStrings
    #QMAKE_CXXFLAGS += /wd"4251"
    #DEFINES += _WIN32
}

# Input
SOURCES += ./main.cpp\
    ./adb_tool.cpp \  
    softconfigdlg.cpp \
    MessageBox.cpp

HEADERS  += ./upgrade_tool.pro \
    ./adb_tool.h \
    softconfigdlg.h \
    MessageBox.h

FORMS    += ./adb_tool.ui \
    softconfigdlg.ui

RESOURCES += HTDEMO.qrc
RC_FILE = HTDEMO.rc

#-------------------------------------------------------------------
COMMON_PRI=$$PWD/../common.pri
exists($$COMMON_PRI) {
    include($$COMMON_PRI)
}else {
    error("FATAL error: can not find common.pri")
}


COMMON2_PRI+=$$PWD/Common/common.pri
exists($$COMMON2_PRI) {
    include($$COMMON2_PRI)
}else {
    error("FATAL error: can not find common.pri")
}

DISTFILES += \
    RFIDAPI.def

