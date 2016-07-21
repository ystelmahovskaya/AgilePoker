TEMPLATE = app

QT += qml quick websockets
CONFIG += c++11

SOURCES += main.cpp \
    agilewebsocketserver.cpp \
    usersmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    agilewebsocketserver.h \
    usersmodel.h
