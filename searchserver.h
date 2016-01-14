#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include <QObject>
class QUdpSocket;
class SearchServer : public QObject
{
    Q_OBJECT
public:
    explicit SearchServer(QObject *parent = 0);

signals:

public slots:
    void startSearch(int port);
private:
    QUdpSocket *_udpSocket;
};

#endif // SEARCHSERVER_H
