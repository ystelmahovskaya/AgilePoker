#include "searchserver.h"
#include <QUdpSocket>

SearchServer::SearchServer(QObject *parent) : QObject(parent)
{
    _udpSocket = new QUdpSocket;
}

void SearchServer::startSearch(int port)
{
    QByteArray datagram = "Are you AgilePocker?";
    _udpSocket->bind(port + 1, QUdpSocket::ShareAddress);
    connect(_udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    _udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, port);
}

void SearchServer::processPendingDatagrams()
{
    qDebug() << "processPendingDatagrams";
    while (_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "datagram" << datagram;
        if (datagram.contains("Yes, I'm")) {
            qDebug() << "Found agile pocker server at" << sender << senderPort;
        }
    }
}
