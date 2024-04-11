#include "tcpclient.h"

#include <QHostAddress>

TcpClient::TcpClient()
{
    m_ptcpsocket = nullptr;
    m_ptcpsocket = new QTcpSocket();
    connect(m_ptcpsocket,&QTcpSocket::connected,this,&TcpClient::OnConnected);
    connect(m_ptcpsocket,&QTcpSocket::disconnected,this,&TcpClient::OnDisconnected);
    connect(m_ptcpsocket,SIGNAL(SocketError(QAbstractSocket::SocketError)),this,SLOT(OnError(QAbstractSocket::SocketError)));
}

TcpClient::~TcpClient()
{
    if(m_ptcpsocket){
        delete m_ptcpsocket;
        m_ptcpsocket = nullptr;
    }
}

bool TcpClient::connectServer(quint16 port)
{
    m_ptcpsocket->connectToHost(QHostAddress::LocalHost,port);
    if(!m_ptcpsocket->waitForConnected(3000)){
        qDebug()<<"port disConnected";
        return false;
    }
    else {
        connect(m_ptcpsocket,&QTcpSocket::readyRead,this,&TcpClient::OnHandleMessage);
        return true;
    }
}

bool TcpClient::SendMessage(const QString& str)
{
    if(m_ptcpsocket->state() != QAbstractSocket::ConnectedState){
        return false;
    }
    else{
        m_ptcpsocket->write(str.toUtf8()+'\n');//Adobe lightroom 插件接收消息必须以\n结尾
        return m_ptcpsocket->waitForBytesWritten(3000);
    }
}

void TcpClient::OnConnected()
{
    qDebug()<<"connected";
}

void TcpClient::OnDisconnected()
{
    qDebug()<<"Disconnected";
}

void TcpClient::OnError(QAbstractSocket::SocketError err)
{
    qDebug()<<"Error type:"<<err;
}

void TcpClient::OnHandleMessage()
{
    if(m_ptcpsocket->bytesAvailable()>0){
        QString strReadMessage= QString::fromUtf8(m_ptcpsocket->readAll());
        qDebug()<<"readmesg:"<<strReadMessage;
        emit ReceivedMsg(strReadMessage);
    }
}


