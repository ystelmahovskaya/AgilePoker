#ifndef AGILEWEBSOCKETSERVER_H
#define AGILEWEBSOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include <QHostAddress>
class QWebSocketServer;
class QWebSocket;
class QUdpSocket;

struct Users {
    QHostAddress address;
    QString userName;
    QByteArray hash;
};

class AgileWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit AgileWebSocketServer(quint16 port, QObject *parent = 0);
    virtual ~AgileWebSocketServer();

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
    QList<Users> m_loggedUsersList;
    QList<Users> m_usersList;

};

#endif // AGILEWEBSOCKETSERVER_H
