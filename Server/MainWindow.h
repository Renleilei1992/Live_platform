#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMap>
#include <iostream>
using namespace std;

class QTcpServer;
class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);//生成日志函数

private slots:
    void timerUpdate();
    void new_connection_slot();
    void signal_mes_slot(QTcpSocket*,const char*,qint64);

    void on_btn_listen_clicked();

    void on_btn_stop_clicked();

public slots:
    void signal_room_info_slot(QTcpSocket* ,QString ,QString );//接收创建房间成功后的房间信息
    void signal_quitRoom_slot(QTcpSocket* ,QString ,QString );//接收关闭直播间信息
    void signal_enterLiveRoom_slot(QTcpSocket* ,QString ,QString );//接收用户进入直播间信息
    void signal_quitLiveRoom_slot(QTcpSocket* ,QString ,QString );//接收用户离开直播间信息
    void signal_refresh_onlineUser_slot(QTcpSocket* ,QString);//接收刷新直播间在线用户信息信号并处理
    void signal_barrage_slot(QString, QString);               //接收客户端弹幕信息并向直播间内每一个在线用户发送该弹幕

public:
    QMap<QString,QMap<QString,QTcpSocket*> > room_online_map;  //创建一个QMap对象用以存储直播间内的固有信息(roomName,user_online)
//    QMap<QString,QTcpSocket*> user_online_map;                 //创建一个QMap对象用以存储在线用户的固有信息（userName,socket）

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
};

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);//处理日志事件函数 目前为关闭状态（注释）
#endif // MAINWINDOW_H
