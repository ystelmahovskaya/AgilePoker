#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "agilewebsocketserver.h"
#include "usersmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("KotkiSoft");
    QCoreApplication::setOrganizationDomain("kotkisoft.com");
    QCoreApplication::setApplicationName("AgilePokerServer");

    UsersModel usersModel;
    AgileWebSocketServer webSocketServer(2345);
    webSocketServer.setUsersModel(&usersModel);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("webSocketServer", &webSocketServer);
    engine.rootContext()->setContextProperty("usersModel", &usersModel);
    engine.load(QUrl(QStringLiteral("qrc:/agileservermain.qml")));

    return app.exec();
}
