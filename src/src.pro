
#方便一次性编译所有的基础接口库

#各子工程按书写顺序编译，清注意各子工程的依赖关系，被依赖的库应写在前面。

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS +=  WIRELESSRFIDAPI \
            RFIDAPI \           
            WirelessDemo \
            upgrade_tool \
            ReaderManager \

