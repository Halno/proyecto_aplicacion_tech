QT -= gui
QT += sql

TARGET = tests_tech


CONFIG += c++11 console
CONFIG -= app_bundle



# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH *= ../../Proyecto/Websocket/

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        ../../Proyecto/Websocket/usuario.cpp \
        ../../Proyecto/Websocket/entrada.cpp \
    testeo.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    testeo.h \
    ../../Proyecto/Websocket/usuario.h \
    ../../Proyecto/Websocket/entrada.h \
    doctest.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../compiled/lib/release/ -lixwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../compiled/lib/debug/ -lixwebsocket
else:unix: LIBS += -L$$PWD/../../../../compiled/lib/ -lixwebsocket

INCLUDEPATH += $$PWD/../../../../compiled/include
DEPENDPATH += $$PWD/../../../../compiled/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../compiled/lib/release/libixwebsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../compiled/lib/debug/libixwebsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../compiled/lib/release/ixwebsocket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../compiled/lib/debug/ixwebsocket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../compiled/lib/libixwebsocket.a
