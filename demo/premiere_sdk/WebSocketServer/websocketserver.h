#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H
#include <QObject>

#ifdef Q_OS_WIN
typedef void (__stdcall *DEVCONNECTION_CALL)();
#endif
class QWebSocket;
class QWebSocketServer;

class WebSocketServer:public QObject
{
    Q_OBJECT
public:
    WebSocketServer(quint16 port);
    ~WebSocketServer();
    void RegisterCallback(DEVCONNECTION_CALL devconnection_call);
    void SendMessage(const QString &message);
signals:
    void ReceivedMsg(const QString& str);
public slots:
    void OnNewConnection();
    void OnClosed();
    void processTextMessage(const QString &message);
    void processBinaryMessage(const QByteArray &message);
    void socketDisconnected();


private:
    QWebSocket* m_pQWebSocket;
    QWebSocketServer* m_pWebSocketServer;
    DEVCONNECTION_CALL m_devconnection_call;
};

#endif // WEBSOCKETSERVER_H
