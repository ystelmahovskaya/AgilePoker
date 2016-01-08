#include "agilewebsocketserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>

AgileWebSocketServer::AgileWebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Chat Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &AgileWebSocketServer::onNewConnection);
    }

}


AgileWebSocketServer::~AgileWebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void AgileWebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &AgileWebSocketServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &AgileWebSocketServer::socketDisconnected);

    m_clients << pSocket;
    qDebug() << "New connection" << pSocket->localAddress() << pSocket->peerAddress();
}

void AgileWebSocketServer::processMessage(QString message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Message:" << message << "from" << pSender->localAddress();
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
//        if (pClient != pSender) //don't echo message back to sender
//        {
//            pClient->sendTextMessage(message);
//        }
    }
}

void AgileWebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        qDebug() << pClient->localAddress() << "disconneted";
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
