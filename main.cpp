#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

int data = 5;
int data1;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv); //for start program

    QGuiApplication *appppp = &app;
    qDebug() << appppp << (char)(*((char*)appppp+10));
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    int ret = app.exec();
    qDebug() << ret;
    qDebug() << "app deleted";
    return ret;
}
