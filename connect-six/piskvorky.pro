
QT += core \
    widgets \
    network
TARGET = piskvorky
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    item.cpp \
    board.cpp \
    server.cpp \
	client.cpp
HEADERS += mainwindow.h \
    item.h \
    board.h \
    server.h \
	client.h
FORMS += mainwindow.ui
RESOURCES += resource.qrc

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000
