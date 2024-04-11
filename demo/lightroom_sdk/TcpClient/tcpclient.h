#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>

class TcpClient:public QObject
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();
    bool connectServer(quint16 port);
    bool SendMessage(const QString &str);
signals:
    void ReceivedMsg(const QString& str);
private slots:
    void OnConnected();
    void OnDisconnected();
    void OnError(QAbstractSocket::SocketError err);
    void OnHandleMessage();
private:
    QTcpSocket* m_ptcpsocket;
};

#endif // TCPCLIENT_H
