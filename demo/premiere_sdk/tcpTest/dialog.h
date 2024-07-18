#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class WebSocketServer;
class QTimer;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    static void __stdcall DevConnection();
    void ShowConnection();

private slots:
    void on_pushButton_clicked();
    void OnReceivedMsg(const QString& str);
    void OnTimeOut();

private:
    Ui::Dialog *ui;
    WebSocketServer* m_pWebSocketServer;
    QTimer* m_pTimer;
};
#endif // DIALOG_H
