QT       -= core gui
CONFIG -= qt

TEMPLATE = lib
TARGET = WIRELESSRFIDAPI

INCLUDEPATH += . \
               ../../platform/

DEFINES += WIRELESS_RFIDAPI_EXPORTS
win32{
    QMAKE_CXXFLAGS -= -Zc:strictStrings
    #QMAKE_CXXFLAGS += /wd"4251"
    #DEFINES += _WIN32
}

# Input
HEADERS += \ 
    BuffList.h \
    CmdBuffer.h \
    CNGetMsg.h \
    ComConn.h \
    ConnetBase.h \
    ConnetCreater.h \
    DataProc.h \
    ENGetMsg.h \
    ErrorMsgFactory.h \
    ErrorProcess.h \
    Global.h \
    IConnect.h \
    IDataProc.h \
    IFactoryConn.h \
    IGetMsgInterface.h \
    IReaderFactory.h \
    Lock.h \
    MsgManager.h \
    RFIDFrame.h \
    RFIDReader.h \
    RFIDReaderManager.h \
    RFIDReaderServer.h \
    RingBuff.h \
    SAATReaderFactory.h \
    Singleton.h \
    stdafx.h \
    TCPConn.h \
    TCPProcCtrl.h \
    TcpServerConn.h \
    TWGetMsg.h \
    UDPConn.h \
    USBConn.h \
    ../../platform/WIRELESSRFIDAPIEXPORT.h

SOURCES += \ 
    BuffList.cpp \
    CmdBuffer.cpp \
    CNGetMsg.cpp \
    ComConn.cpp \
    ConnetBase.cpp \
    ConnetCreater.cpp \
    DataProc.cpp \
    ENGetMsg.cpp \
    ErrorMsgFactory.cpp \
    ErrorProcess.cpp \
    Global.cpp \
    IConnect.cpp \
    IDataProc.cpp \
    IFactoryConn.cpp \
    IGetMsgInterface.cpp \
    IReaderFactory.cpp \
    Lock.cpp \
    MsgManager.cpp \
    RFIDAPI.cpp \
    RFIDFrame.cpp \
    RFIDReader.cpp \
    RFIDReaderManager.cpp \
    RFIDReaderServer.cpp \
    RingBuff.cpp \
    SAATReaderFactory.cpp \
    stdafx.cpp \
    TCPConn.cpp \
    TCPProcCtrl.cpp \
    TcpServerConn.cpp \
    TWGetMsg.cpp \
    UDPConn.cpp \
    USBConn.cpp \
    WIRELESSRFIDAPIEXPORT.cpp


#-------------------------------------------------------------------
COMMON_PRI=$$PWD/../common.pri
exists($$COMMON_PRI) {
    include($$COMMON_PRI)
}else {
    error("FATAL error: can not find common.pri")
}

DISTFILES += \
    RFIDAPI.def

SUBDIRS += \
    WIRELESSRFIDAPI.pro

