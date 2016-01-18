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
    void foundServer(QString serverAddress);

public slots:
    void startSearch(int port);
private slots:
    void processPendingDatagrams();
private:
    QUdpSocket *_udpSocket;
};

#endif // SEARCHSERVER_H
