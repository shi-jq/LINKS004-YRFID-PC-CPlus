QT       -= core gui
CONFIG -= qt

TEMPLATE = lib
TARGET = RFIDAPI

INCLUDEPATH += . \
               ../../platform/

DEFINES += RFIDAPI_EXPORTS
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
    COMConn.h \
    DataProc.h \
    ENGetMsg.h \
    ErrorMsgFactory.h \
    ErrorProcess.h \
    Global.h \
    IConnect.h \
    IDataProc.h \
    IFactoryConn.h \
    IGetMsgInterface.h \
    IReader.h \
    IReaderFactory.h \
    MsgManager.h \
    RFIDCardBuffer.h \
    RFIDReader.h \
    RFIDReaderManager.h \
    SAATReaderFactory.h \
    stdafx.h \
    TCPConn.h \
    language/CNGetMsg.h \
    language/ENGetMsg.h \
    language/ErrorMsgFactory.h \
    language/IGetMsgInterface.h \
    language/MsgManager.h \
    language/TWGetMsg.h \
    ../../platform/RFIDAPIEXPORT.h \
    UDPConn.h \
    USBConn.h

SOURCES += \ 
    BuffList.cpp \
    CmdBuffer.cpp \
    CNGetMsg.cpp \
    COMConn.cpp \
    DataProc.cpp \
    ENGetMsg.cpp \
    ErrorMsgFactory.cpp \
    ErrorProcess.cpp \
    Global.cpp \
    IConnect.cpp \
    IDataProc.cpp \
    IFactoryConn.cpp \
    IGetMsgInterface.cpp \
    IReader.cpp \
    IReaderFactory.cpp \
    MsgManager.cpp \
    RFIDAPI.cpp \
    RFIDAPIEXPORT.cpp \
    RFIDCardBuffer.cpp \
    RFIDReader.cpp \
    RFIDReaderManager.cpp \
    SAATReaderFactory.cpp \
    stdafx.cpp \
    TCPConn.cpp \
    TWGetMsg.cpp \
    language/CNGetMsg.cpp \
    language/ENGetMsg.cpp \
    language/ErrorMsgFactory.cpp \
    language/IGetMsgInterface.cpp \
    language/MsgManager.cpp \
    language/TWGetMsg.cpp \
    UDPConn.cpp \
    USBConn.cpp


#-------------------------------------------------------------------
COMMON_PRI=$$PWD/../common.pri
exists($$COMMON_PRI) {
    include($$COMMON_PRI)
}else {
    error("FATAL error: can not find common.pri")
}

DISTFILES += \
    RFIDAPI.def

