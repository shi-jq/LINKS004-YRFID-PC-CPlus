
#所有工程的pro文件应包含（include）本文件
#包含位置应当在pro文件的末尾

CODE_HOME = $$PWD/..

#---------------------------------------------------------------------------------------------------

#虽然Unix、Linux下不要求严格区分，但是为了便于管理，所有平台区分Debug、Release
CONFIG(debug, debug|release) {
    DIR_DEBUG_RELEASE=_debug
}
CONFIG(release, debug|release) {
    DIR_DEBUG_RELEASE=_release
}

#---------------------------------------------------------------------------------------------------

linux-g++* {
    message("current os-compiler linux-g++")

    #程序中可判断此宏定义进行条件编译
    DEFINES += OS_LINUX

    #避免gcc 4.8 报警：boost/optional/optional.hpp:968:5: 警告：未使用的参数‘rhs’
    #原因是gcc该函数的默认实现中没有使用rhs参数，换用BOOST定义的实现
    DEFINES += BOOST_OPTIONAL_DETAIL_NO_DEFAULTED_MOVE_FUNCTIONS=1
}

win32-msvc* {
    message("current os-compiler windows-msvc")

    #程序中可判断此宏定义进行条件编译
    DEFINES += OS_WINDOWS

    #设置程序的运行时字符编码
    QMAKE_CXXFLAGS+=/execution-charset:utf-8

    LIBS += -lws2_32
	

}

contains(QT_ARCH, i386) {
    DIR_ARCH=32
} else {
    DIR_ARCH=64
}

solaris-g++* {
    message("current os-compiler solaris-g++")

    #程序中可判断此宏定义进行条件编译
    DEFINES += OS_SOLARIS

    LIBS += -ldl \
            -lw \
            -lgen
}

#关闭BOOST的自动连库
DEFINES += BOOST_ALL_NO_LIB=1

#BOOST使用动态库
DEFINES += BOOST_ALL_DYN_LINK=1

#---------------------------------------------------------------------------------------------------

isEmpty(TARGET) {
    error("Error, TARGET is empty!")
}
else {
    #设置编译过程临时文件的路径，保持源代码目录清洁
    MOC_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/moc
    UI_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/ui
    UI_HEADERS_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/ui/include
    UI_SOURCES_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/ui/src
    OBJECTS_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/obj
    RCC_DIR = $$CODE_HOME/temp/$$TARGET$$DIR_DEBUG_RELEASE/rcc
}

message("OBJECTS_DIR =" $$OBJECTS_DIR)

#---------------------------------------------------------------------------------------------------

#取消为生成的动态库创建软链接，减少文件数量
CONFIG += unversioned_libname unversioned_soname

#设置运行时找动态库的路径rpath，对采用ELF文件格式的系统有效（Unix、Linux）
#“$ORIGIN”为文件所在路径，多个路径间用英文冒号分隔
#Windows下优先在程序所在目录找动态库
QMAKE_RPATHDIR += :\'\$\$ORIGIN\'

#编译器找头文件的路径
INCLUDEPATH += $$CODE_HOME/src/include \

#连接器找直接链接的库的路径
LIBS += -L$$CODE_HOME/platform/$$DIR_DEBUG_RELEASE$$DIR_ARCH/

#连接器找隐含依赖（直接链接的库所链接的库）库的路径
QMAKE_RPATHLINKDIR += $$CODE_HOME/platform/$$DIR_DEBUG_RELEASE$$DIR_ARCH/

#生成路径，可执行文件和库文件都放在一起
DESTDIR = $$CODE_HOME/platform/$$DIR_DEBUG_RELEASE$$DIR_ARCH/

message("DESTDIR =" $$DESTDIR)



