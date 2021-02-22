HEADERS  += \
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
./Common/BuzzerSpeakerCtrl.h

SOURCES += \
  ./Common/widgetconfig.cpp \
./Common/mainapp.cpp \
    ./Common/appconfig.cpp \
    ./Common/SetDebugNew.cpp \
 ./Common/CheckTime.cpp \
    ./Common/LanguageSrc.cpp \
    ./Common/maininit.cpp  \
        ./Common/Lock.cpp \
 ./Common/BuzzerSpeakerCtrl.cpp


INCLUDEPATH +=  ./Common/
