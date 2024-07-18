#include "dialog.h"
#include "websocketserver.h"
#include "ui_dialog.h"
#include <QTimer>

Dialog* g_pDialog = nullptr;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_pWebSocketServer = nullptr;
    m_pWebSocketServer = new WebSocketServer(12345);
    m_pWebSocketServer->RegisterCallback(DevConnection);
//    connect(m_pWebSocketServer,&WebSocketServer::ReceivedMsg,this,&Dialog::OnReceivedMsg);

    g_pDialog = this;

    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&Dialog::OnTimeOut);
    m_pTimer->start(2000);
}

Dialog::~Dialog()
{
    delete ui;
    delete m_pWebSocketServer;
    m_pWebSocketServer = nullptr;
}

void Dialog::DevConnection()
{
    g_pDialog->ShowConnection();
}

void Dialog::ShowConnection()
{
    QString str;
    str = ui->textEdit->toPlainText();
    ui->textEdit->setText(str+"new connection!\n");
}


void Dialog::on_pushButton_clicked()
{
    m_pWebSocketServer->SendMessage("crop|0|0|+1\n");
}

void Dialog::OnReceivedMsg(const QString &str)
{
    ui->textEdit->setText(str);
}

void Dialog::OnTimeOut()
{
    m_pWebSocketServer->SendMessage("crop|5|0|-3\n");
}


