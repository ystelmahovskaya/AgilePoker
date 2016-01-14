#include "searchserver.h"
#include <QUdpSocket>

SearchServer::SearchServer(QObject *parent) : QObject(parent)
{
    _udpSocket = new QUdpSocket;
}

void SearchServer::startSearch(int port)
{
    QByteArray datagram = "Are you AgilePocker?";
    _udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, port);
}
