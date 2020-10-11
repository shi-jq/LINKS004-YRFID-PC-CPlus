#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T10:02:43
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReaderManager
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

LIBS += -lRFIDAPI

DEPENDPATH += .
INCLUDEPATH += ../bin
INCLUDEPATH += ./

win32: {
        DEFINES += WIN32
        #DEFINES -= UNICODE
        LIBS += -lws2_32 -lOle32
}

RESOURCES += HTDEMO.qrc

RC_FILE = HTDEMO.rc

SOURCES += ./main.cpp \
    ./mainwindow.cpp \
    ./connetdlg.cpp \
    ./workdpacedlg.cpp \
    ./oplistdlg.cpp \
    ./mainapp.cpp \
    ./appconfig.cpp \
    forwardconfigdlg.cpp \
    forwardsetdlg.cpp \
    tabforwardconfigform.cpp \
    ./SetDebugNew.cpp \
    ./udpclient.cpp \
    ./UdpWorkerThread.cpp \
    ./CheckTime.cpp \
    ./LanguageSrc.cpp \
    ./maininit.cpp  \
    ./readermanager.cpp \
    ./readerdllbase.cpp \
    ./widgetconfig.cpp \
    #./readerdllcommon.cpp \
    ./Lock.cpp \
    ./readcardfor6cdlg.cpp \
    ./readconfigfor6cdlg.cpp \
    ./ReadCardFor6CThread.cpp \
    ./BuzzerSpeakerCtrl.cpp \
    #./tagopfor6cdlg.cpp \
    #./tagreadfor6cdlg.cpp \
    #./tagwritefor6cdlg.cpp \
    #./taglockfor6cdlg.cpp \
    #./tagkillfor6cdlg.cpp \
    #./tagerasefor6cdlg.cpp \
    #./tagselectfor6cdlg.cpp \
    ./firmwareupdatefor6cdlg.cpp \
    netconfigfor6cdlg.cpp \
    comconfigdlg.cpp \
    busaddrconfigdlg.cpp \
    readertimesetdlg.cpp \
    flashconfigfor6cdlg.cpp \
    filtratetagfor6cdlg.cpp \
    ioconfigfor6cdlg.cpp \
    paramconfigfor6cdlg.cpp \
    qvaluedlg.cpp \
    gprsconfigdlg.cpp \
    guidemaindlg.cpp \
    languagesetdlg.cpp \
    softconfigdlg.cpp \
    ./tcpclient.cpp \ 
    MessageBox.cpp \
    progressbardlg.cpp \
    helpfor6cdlg.cpp \
    versioncommondlg.cpp \
    #tagtestfor6cdlg.cpp \
    paramadd6cdlg.cpp \
    tabsysinfoform.cpp \
    tabconnetinfoform.cpp \
    tabapplyinfoform.cpp \
    readerinfo6cform.cpp \
    rebootdeviceform.cpp \
    tabparamconfigform.cpp \
    tabuploadform.cpp \
    uploadpramform.cpp \
    weigenconfigform.cpp \
    antennaprmform.cpp \
    pointconfigform.cpp \
    carrierconfigform.cpp \
    writeeidform.cpp \
    readwritedataform.cpp \
    pwdsetform.cpp \
    lockopform.cpp \
    findtagform.cpp \
    tagopdialog.cpp \
    tagfilterform.cpp \
    buzzerconfigform.cpp
    
HEADERS  += ./mainwindow.h \
    ./connetdlg.h \
    ./workdpacedlg.h \
    ./oplistdlg.h \
    ./Singleton.h \
    ./mainapp.h \
    ./appconfig.h \
    ../bin/RFIDAPIEXPORT.h \
    ./SetDebugNew.h \
    ./udpclient.h \
    ./UdpWorkerThread.h \
    ./CheckTime.h\
    ./LanguageSrc.h \
    ./AppPath.h \
    ./maininit.h \
    ./readermanager.h \
    ./readerdllbase.h \
    ./widgetconfig.h \
    #./readerdllcommon.h \
    ./Lock.h \
    ./readcardfor6cdlg.h \
    ./readconfigfor6cdlg.h \
    ./ReadCardFor6CThread.h \
    ./BuzzerSpeakerCtrl.h \
    #./tagopfor6cdlg.h \
    #./tagreadfor6cdlg.h \
    #./tagwritefor6cdlg.h \
    #./taglockfor6cdlg.h \
    #./tagkillfor6cdlg.h \
    #./tagerasefor6cdlg.h \
    #./tagselectfor6cdlg.h \
    ./firmwareupdatefor6cdlg.h \
    forwardconfigdlg.h \
    forwardsetdlg.h \
    netconfigfor6cdlg.h \
    comconfigdlg.h \
    busaddrconfigdlg.h \
    readertimesetdlg.h \
    flashconfigfor6cdlg.h \
    filtratetagfor6cdlg.h \
    ioconfigfor6cdlg.h \
    paramconfigfor6cdlg.h \
    qvaluedlg.h \
    gprsconfigdlg.h \
    guidemaindlg.h \
    languagesetdlg.h \
    softconfigdlg.h \
    ./tcpclient.h \  \
    tabforwardconfigform.h \
    MessageBox.h \
    progressbardlg.h \
    helpfor6cdlg.h \
    versioncommondlg.h \
    #tagtestfor6cdlg.h \
    paramadd6cdlg.h \
    tabsysinfoform.h \
    tabconnetinfoform.h \
    tabapplyinfoform.h \
    readerinfo6cform.h \
    rebootdeviceform.h \
    tabparamconfigform.h \
    tabuploadform.h \
    uploadpramform.h \
    weigenconfigform.h \
    antennaprmform.h \
    pointconfigform.h \
    carrierconfigform.h \
    writeeidform.h \
    readwritedataform.h \
    pwdsetform.h \
    lockopform.h \
    findtagform.h \
    tagopdialog.h \
    tagfilterform.h \
    buzzerconfigform.h

FORMS    += ./mainwindow.ui \
    ./connetdlg.ui \
    ./workdpacedlg.ui \
    ./oplistdlg.ui \
    forwardconfigdlg.ui \
    forwardsetdlg.ui \
    tabforwardconfigform.ui \
    ./readcardfor6cdlg.ui \
    ./readconfigfor6cdlg.ui \
    #./tagopfor6cdlg.ui \
    #./tagreadfor6cdlg.ui \
    #./tagwritefor6cdlg.ui \
    #./taglockfor6cdlg.ui \
    #./tagkillfor6cdlg.ui \
    #./tagerasefor6cdlg.ui \
    #./tagselectfor6cdlg.ui \
    ./firmwareupdatefor6cdlg.ui \
    netconfigfor6cdlg.ui \
    comconfigdlg.ui \
    busaddrconfigdlg.ui \
    readertimesetdlg.ui \
    flashconfigfor6cdlg.ui \
    filtratetagfor6cdlg.ui \
    ioconfigfor6cdlg.ui \
    paramconfigfor6cdlg.ui \
    qvaluedlg.ui \
    gprsconfigdlg.ui \
    guidemaindlg.ui \
    languagesetdlg.ui \
    softconfigdlg.ui \
    progressbardlg.ui \
    helpfor6cdlg.ui \
    versioncommondlg.ui \
    #tagtestfor6cdlg.ui \
    paramadd6cdlg.ui \
    tabsysinfoform.ui \
    tabconnetinfoform.ui \
    tabapplyinfoform.ui \
    readerinfo6cform.ui \
    rebootdeviceform.ui \
    tabparamconfigform.ui \
    tabuploadform.ui \
    uploadpramform.ui \
    weigenconfigform.ui \
    antennaprmform.ui \
    pointconfigform.ui \
    carrierconfigform.ui \
    writeeidform.ui \
    readwritedataform.ui \
    pwdsetform.ui \
    lockopform.ui \
    findtagform.ui \
    tagopdialog.ui \
    tagfilterform.ui \
    buzzerconfigform.ui



