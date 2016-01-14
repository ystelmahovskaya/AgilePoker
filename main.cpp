#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "searchserver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv); //for start program

    QQmlApplicationEngine engine;
    SearchServer searchServer;
    engine.rootContext()->setContextProperty("searchServer", &searchServer);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    int ret = app.exec();
    return ret;
}
