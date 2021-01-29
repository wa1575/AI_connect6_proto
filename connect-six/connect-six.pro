#bob9 six connect

QT += core \
    widgets \
    network
TARGET = connect-six
TEMPLATE = app
SOURCES += main.cpp \
    ai.cpp \
    mainwindow.cpp \
    item.cpp \
    board.cpp \
    player.cpp \
    server.cpp \
    client.cpp
HEADERS +=     mainwindow.h \
    ai.h \
    item.h \
    board.h \
    player.h \
    server.h \
    client.h \
    stdafx.h




FORMS += mainwindow.ui
RESOURCES += resource.qrc

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bob9-connect6/connect6_protocol/release/ -lconnect6_protocol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bob9-connect6/connect6_protocol/debug/ -lconnect6_protocol
else:unix: LIBS += -L$$PWD/../../bob9-connect6/connect6_protocol/ -lconnect6_protocol

INCLUDEPATH += $$PWD/../../bob9-connect6/connect6_protocol
DEPENDPATH += $$PWD/../../bob9-connect6/connect6_protocol
