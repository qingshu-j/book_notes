QT       += core gui network
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h \

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/ -lWebSocketServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/ -lWebSocketServerd

INCLUDEPATH += $$PWD/../WebSocketServer
DEPENDPATH += $$PWD/../WebSocketServer

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/libWebSocketServer.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/libWebSocketServerd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/WebSocketServer.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-WebSocketServer-Desktop_Qt_5_6_0_vs2010_32-Debug/debug/WebSocketServerd.lib
