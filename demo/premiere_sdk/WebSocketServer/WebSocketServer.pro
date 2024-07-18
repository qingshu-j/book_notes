QT -= gui
QT += core network
QT += websockets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    websocketserver.cpp

HEADERS += \
    websocketserver.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(debug,debug|release):TARGET = WebSocketServerd
else:win32:CONFIG(release,debug|release):TARGET = WebSocketServer
