#include "agilewebsocketserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QUdpSocket>
#include <QtCore/QDebug>

AgileWebSocketServer::AgileWebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients(),
    m_port(port)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Chat Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &AgileWebSocketServer::onNewConnection);
        _udpSocket = new QUdpSocket;
        _udpSocket->bind(port, QUdpSocket::ShareAddress);
        connect(_udpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));
    }

}

void AgileWebSocketServer::processPendingDatagrams()
{
    while (_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if (datagram.contains("Are you AgilePocker?")) {
            qDebug() << "Found agile pocker client at" << sender << senderPort;
            QByteArray datagramAnswer;
            datagramAnswer = "Yes, I'm";
            qint64 written = _udpSocket->writeDatagram(datagramAnswer.data(), datagramAnswer.size(),
                                     sender, m_port + 1);
            qDebug() << "server send" << written << "bytes to" << sender << m_port;
        }
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
