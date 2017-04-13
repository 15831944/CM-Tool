#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QWidget>
#include<QUdpSocket>
#include<QHostAddress>
#include<QMessageBox>
#include<QDebug>

class HeartBeat : public QWidget
{
    Q_OBJECT
public:
    explicit HeartBeat(QWidget *parent = 0,int port = 0);

    QHostAddress getAddr();
    quint16 getPort();
    QString getData();
    void sendData(QByteArray &array);

signals:

public slots:
    void dataReceived();

protected:
    QUdpSocket *mUdpScoket;
    QHostAddress *mAddr;
    quint16 *mPort;
    QString data;

protected:
    void initData();
};
HeartBeat *get_HeartBeat();

#endif // HEARTBEAT_H
