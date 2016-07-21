#ifndef AGILEWEBSOCKETSERVER_H
#define AGILEWEBSOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QHostAddress>
#include "usersmodel.h"
class QWebSocketServer;
class QWebSocket;
class QUdpSocket;


class AgileWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit AgileWebSocketServer(quint16 port, QObject *parent = 0);
    virtual ~AgileWebSocketServer();

    Q_INVOKABLE UsersModel *getUsersModel();

    void setUsersModel(UsersModel *value);

private Q_SLOTS:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();
    void processPendingDatagrams();
    void addNewUser(const QString &message);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QUdpSocket *_udpSocket;
    int m_port;
    UsersModel *usersModel;
};

#endif // AGILEWEBSOCKETSERVER_H
