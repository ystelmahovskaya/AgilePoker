#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "agilewebsocketserver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("KotkiSoft");
    QCoreApplication::setOrganizationDomain("kotkisoft.com");
    QCoreApplication::setApplicationName("AgilePokerServer");
    AgileWebSocketServer webSocketServer(2345);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/agileservermain.qml")));

    return app.exec();
}
