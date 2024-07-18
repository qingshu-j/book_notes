#include "websocketserver.h"
#include <QWebSocket>
#include <QWebSocketServer>
#include <QHostAddress>

WebSocketServer::WebSocketServer(quint16 port)
{
    m_devconnection_call = nullptr;
    m_pQWebSocket = nullptr;
    m_pWebSocketServer = nullptr;
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("premiere webServer"),QWebSocketServer::NonSecureMode, this);
    if(m_pWebSocketServer->listen(QHostAddress::LocalHost,port)){
        connect(m_pWebSocketServer,&QWebSocketServer::newConnection,this,&WebSocketServer::OnNewConnection);
        connect(m_pWebSocketServer,&QWebSocketServer::closed,this,&WebSocketServer::OnClosed);
    }
}

WebSocketServer::~WebSocketServer()
{
    OnClosed();
}

void WebSocketServer::RegisterCallback(DEVCONNECTION_CALL devconnection_call)
{
    m_devconnection_call = devconnection_call;
}

void WebSocketServer::SendMessage(const QString &message)
{
    if(m_pQWebSocket){
        m_pQWebSocket->sendTextMessage(message);
    }
}


void WebSocketServer::OnNewConnection()
{
    if(m_pQWebSocket){
        return;
    }
    QWebSocket* pQWebSocket = m_pWebSocketServer->nextPendingConnection();
    connect(pQWebSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(pQWebSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    connect(pQWebSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);
    m_pQWebSocket = pQWebSocket;

    m_devconnection_call();
//    processTextMessage("crop|0|0|+1\n");
    //    m_clients << pQWebSocket;
}

void WebSocketServer::OnClosed()
{
    m_pWebSocketServer->close();
    if(m_pWebSocketServer){
        delete m_pWebSocketServer;
        m_pWebSocketServer = nullptr;
    }
    m_pQWebSocket = nullptr;
    m_devconnection_call = nullptr;
}

void WebSocketServer::processTextMessage(const QString &message)
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    if(pClient){
        pClient->sendTextMessage(message);
    }
}

void WebSocketServer::processBinaryMessage(const QByteArray &message)
{
    QWebSocket* pClient = qobject_cast<QWebSocket*>(sender());
    if(pClient){
        pClient->sendBinaryMessage(message);
    }
}

void WebSocketServer::socketDisconnected()
{
    m_pQWebSocket = nullptr;
}
