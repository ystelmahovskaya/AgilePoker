#ifndef AGILEWEBSOCKETSERVER_H
#define AGILEWEBSOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

class QWebSocketServer;
class QWebSocket;
class QUdpSocket;

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

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QUdpSocket *_udpSocket;
};

#endif // AGILEWEBSOCKETSERVER_H
