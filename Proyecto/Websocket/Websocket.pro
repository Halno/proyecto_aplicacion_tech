QT -= gui
QT += sql

TARGET = tech
TEMPLATE = app

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    usuario.cpp \
    seccion.cpp \
    entrada.cpp \
    servidor.cpp

LIBS += -pthread -lz

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../websocket/IXWebSocket/build/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../websocket/IXWebSocket/build/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../websocket/IXWebSocket/build/ -lixwebsocket

INCLUDEPATH += $$PWD/../../websocket/IXWebSocket/build
DEPENDPATH += $$PWD/../../websocket/IXWebSocket/build

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/libixwebsocket.a

DISTFILES += \
    ../../Escritorio/miservidorwebsocket/miservidorwebsocket.pro.user

HEADERS += \
    json.hpp \
    usuario.h \
    seccion.h \
    entrada.h \
    servidor.h

SUBDIRS += \
    ../../Escritorio/miservidorwebsocket/miservidorwebsocket.pro \
    ../../Escritorio/miservidorwebsocket/miservidorwebsocket.pro

FORMS += \
    ../../Escritorio/miservidorwebsocket/mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../websocket/IXWebSocket/build/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../websocket/IXWebSocket/build/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../websocket/IXWebSocket/build/ -lixwebsocket

INCLUDEPATH += $$PWD/../../websocket/IXWebSocket/build
DEPENDPATH += $$PWD/../../websocket/IXWebSocket/build

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../websocket/IXWebSocket/build/libixwebsocket.a
