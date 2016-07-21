#include "agilewebsocketserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QUdpSocket>
#include <QStringList>
#include <QString>
#include <QtCore/QDebug>
#include <QSettings>
#include <QQmlEngine>

AgileWebSocketServer::AgileWebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients(),
    m_port(port)
{
    QSettings settings;
    int size = settings.beginReadArray("users");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        Users users;
        users.userName = settings.value("userName").toString();
        users.hash = settings.value("hash").toByteArray();
        //m_usersList.append(users);
    }
    settings.endArray();

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

//NEWUSER;USER:<username>;PASSWORD:<password>
void AgileWebSocketServer::addNewUser(const QString &message) {
    QStringList l1 = message.split(";");
    if (l1.count() != 3) {
        qWarning() << "Invalid newuser message" << message;
        return;
    }
    QStringList user = l1.at(1).split(":");
    if (user.count() != 2) {
        qWarning() << "Invalid user in newuser message" << message;
        return;
    }
    QStringList pass = l1.at(2).split(":");
    if (pass.count() != 2) {
        qWarning() << "Invalid password in newuser message" << message;
        return;
    }
    Users users;
    users.userName = user.at(1);
    users.hash = QCryptographicHash::hash(QByteArray(user.at(1).toUtf8() + pass.at(1).toUtf8()),
                                          QCryptographicHash::Sha1);
    //m_usersList.append(users);
//    QSettings settings;
//    settings.beginWriteArray("users");
//    for (int i = 0; i < m_usersList.size(); ++i) {
//        settings.setArrayIndex(i);
//        settings.setValue("userName", m_usersList.at(i).userName);
//        settings.setValue("hash", m_usersList.at(i).hash);
//    }
//    settings.endArray();
}

void AgileWebSocketServer::setUsersModel(UsersModel *value)
{
    usersModel = value;
}

UsersModel *AgileWebSocketServer::getUsersModel()
{
    return usersModel;
}

void AgileWebSocketServer::processMessage(QString message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Message:" << message << "from" << pSender->localAddress();
//    if (message.startsWith("NEWUSER")) {
//        addNewUser(message);
//    }
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
