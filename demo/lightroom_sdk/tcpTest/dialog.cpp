#include "dialog.h"
#include "tcpclient.h"
#include "ui_dialog.h"

#include <QTimer>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_pReadtcp = nullptr;
    m_pWritetcp = nullptr;
    m_pReadtcp = new TcpClient();
    m_pReadtcp->connectServer(19967);//Adobe lightroom 插件socket 收发消息的端口需不一致
    connect(m_pReadtcp,&TcpClient::ReceivedMsg,this,&Dialog::OnReceivedMsg);
    m_pWritetcp = new TcpClient();
    m_pWritetcp->connectServer(19966);

    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&Dialog::OnTimeOut);
    m_pTimer->start(2000);
}

Dialog::~Dialog()
{
    delete ui;
    delete m_pReadtcp;
    delete m_pWritetcp;
    m_pReadtcp = nullptr;
    m_pWritetcp = nullptr;
}


void Dialog::on_pushButton_clicked()
{
    m_pWritetcp->SendMessage("Temperature|色温|-3");
}

void Dialog::OnReceivedMsg(const QString &str)
{
    ui->textEdit->setText(str);
}

void Dialog::OnTimeOut()
{
    m_pWritetcp->SendMessage("Temperature|色温|-3");
}


