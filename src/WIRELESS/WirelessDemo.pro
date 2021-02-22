#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T10:02:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WirelessDemo
TEMPLATE = app


LIBS += -lWIRELESSRFIDAPI

DEPENDPATH += .
INCLUDEPATH += ../../platform
INCLUDEPATH += ./
INCLUDEPATH += ./Common
INCLUDEPATH += ./CommonUI
INCLUDEPATH += ./wireless

win32: {
        DEFINES += WIN32
        #DEFINES -= UNICODE
        LIBS += -lws2_32 -lOle32
}

RESOURCES += HTDEMO.qrc
RC_FILE = HTDEMO.rc

SOURCES += ./Common/main.cpp\
    ./CommonUI/mainwindow.cpp \   
    ./CommonUI/workdpacedlg.cpp \
    ./CommonUI/oplistdlg.cpp \
    ./Common/mainapp.cpp \
    ./Common/appconfig.cpp \   
    ./Common/SetDebugNew.cpp \
    ./CommonUI/udpclient.cpp \
    ./CommonUI/UdpWorkerThread.cpp \
    ./Common/CheckTime.cpp \
    ./Common/LanguageSrc.cpp \
    ./Common/maininit.cpp  \
    #./Common/readermanager.cpp \
    #./Common/readerdllbase.cpp \
    ./wireless/wirelessrecv.cpp \
    ./Common/widgetconfig.cpp \
    #./Common/readerdllcommon.cpp \
    ./Common/Lock.cpp \
    ./wireless/WirelessRecvCtrl.cpp \
    ./wireless/wirelessadvanceddlg.cpp \
    ./wireless/wirelessdeviceinfodlg.cpp \
    ./wireless/wirelesssysinfowidget.cpp \
    ./wireless/wirelessreadparamwidget.cpp \
    ./wireless/wirelessreadconfigwidget.cpp \
    ./wireless/wirelessioctrlwidget.cpp \ 
    ./Common/BuzzerSpeakerCtrl.cpp \
    CommonUI/guidemaindlg.cpp \
    CommonUI/languagesetdlg.cpp \
    CommonUI/softconfigdlg.cpp \
    CommonUI/MessageBox.cpp \
    CommonUI/progressbardlg.cpp \
    CommonUI/helpfor6cdlg.cpp \
    CommonUI/versioncommondlg.cpp \
    wireless/addclientdlg.cpp \
    wireless/wirelesstcpserverconfigdlg.cpp \ 
    wireless/pointconfigform.cpp \
    wireless/carrierconfigform.cpp \
    wireless/antennaprmform.cpp
    
HEADERS  += ./HTDEMO.pro \
    ./CommonUI/mainwindow.h \
    ./CommonUI/workdpacedlg.h \
    ./CommonUI/oplistdlg.h \
    ./Common/Singleton.h \
    ./Common/mainapp.h \
    ./Common/appconfig.h \
    ../../platform/RFIDAPIEXPORT.h \
    ../../platform/WIRELESSRFIDAPIEXPORT.h \
    ./Common/SetDebugNew.h \
    ./CommonUI/udpclient.h \
    ./CommonUI/UdpWorkerThread.h \
    ./Common/CheckTime.h\
    ./Common/LanguageSrc.h \
    ./Common/AppPath.h \
    ./Common/maininit.h \
    #./Common/readermanager.h \
    #./Common/readerdllbase.h \
    ./wireless/wirelessrecv.h \
    ./Common/widgetconfig.h \
    #./Common/readerdllcommon.h \
    ./Common/Lock.h \
    ./wireless/WirelessRecvCtrl.h \
    ./wireless/wirelessadvanceddlg.h \
    ./wireless/wirelessdeviceinfodlg.h \
    ./wireless/wirelesssysinfowidget.h \
    ./wireless/wirelessreadparamwidget.h \
    ./wireless/wirelessreadconfigwidget.h \
    ./wireless/wirelessioctrlwidget.h \ 
    ./Common/BuzzerSpeakerCtrl.h \
    CommonUI/guidemaindlg.h \
    CommonUI/languagesetdlg.h \
    CommonUI/softconfigdlg.h \
    CommonUI/MessageBox.h \
    CommonUI/progressbardlg.h \
    CommonUI/helpfor6cdlg.h \
    CommonUI/versioncommondlg.h \
    wireless/addclientdlg.h \
    wireless/wirelesstcpserverconfigdlg.h \ 
    wireless/pointconfigform.h \
    wireless/carrierconfigform.h \
    wireless/antennaprmform.h

FORMS    += ./CommonUI/mainwindow.ui \
    ./CommonUI/workdpacedlg.ui \
    ./CommonUI/oplistdlg.ui \    
    ./wireless/wirelessrecv.ui \ 
    ./wireless/wirelessadvanceddlg.ui \
    ./wireless/wirelessdeviceinfodlg.ui \
    ./wireless/wirelesssysinfowidget.ui \
    ./wireless/wirelessreadparamwidget.ui \
    ./wireless/wirelessreadconfigwidget.ui \
    ./wireless/wirelessioctrlwidget.ui \     
    CommonUI/guidemaindlg.ui \
    CommonUI/languagesetdlg.ui \
    CommonUI/softconfigdlg.ui \
    CommonUI/progressbardlg.ui \
    CommonUI/helpfor6cdlg.ui \
    CommonUI/versioncommondlg.ui \  
    wireless/addclientdlg.ui \
    wireless/wirelesstcpserverconfigdlg.ui \ 
    wireless/pointconfigform.ui \
    wireless/carrierconfigform.ui \
    wireless/antennaprmform.ui
	
#-------------------------------------------------------------------
COMMON_PRI=$$PWD/../common.pri
exists($$COMMON_PRI) {
    include($$COMMON_PRI)
}else {
    error("FATAL error: can not find common.pri")
}


