#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>
#include "CreateRoom.h"

namespace Ui {
class MainWindow;
}

class QTcpSocket;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    CreateRoom *createRoom;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_register_clicked();

    void on_btn_login_clicked();

    void readyReadSlot();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;

signals:
    void open_createRoom_window(QString userName);          //打开第二个窗口的信号
    void open_mainWindow();
    void open_room_window_success();    //打开直播间窗口的信号，与创建窗口进行通信,不同于第二窗口发出的信号（注意区分）
    void check_room_info(QString room_name,QString room_addr);//向第二个窗口发出信号，包含在线房间名和房间地址
    void online_user_inLiveRoom(QString onlineUserName,int flagNum);//向第二个窗口发出信号，包含直播间在线用户名
    void signal_barrage_back(QString barrage_back);     //向第二个窗口发出信号，包含弹幕内容（来自服务器）
    void quit_back_infoFromServer(QString quit_liveUserName);//向第二个窗口发出信号，包含离开直播间用户名信息（来自服务器）

public slots:
    void open_createRoom_window_slot(QString userName);     //打开第二个窗口的槽函数,使用hide
    void create_room_window_slot(QString roomName,QString roomAddr);//接收创建房间信号并传递信息到服务器写入数据库
    void check_room_info2_slot();                                   //接收第二个窗口发送的刷新命令查询在线房间名和地址，向服务器发送请求
    void quit_room_slot(QString room_name);     //接收来自第二个窗口发送的房间关闭信号并向服务器发送直播间关闭信息（目的删除数据库中直播间信息）
    void enter_live_userName_slot(QString userName,QString roomName);//接收来自第二窗口发出的进入直播用户名（向服务器发送该用户名进入直播间信息）
    void quit_live_userName_slot(QString userName,QString roomName); //接收来自第二窗口发出的退出直播用户名（向服务器发送该用户名退出直播间信息）
    void send_barrage_toServer_slot(QString msgContent,QString roomName);//接收来自第二窗口的弹幕信息（向服务器发送弹幕信息）
    void offline_Info_slot(QString offline_userName);                //接收来自第二窗口的用户离线信号（向服务器发送用户离线）
};

#endif // MAINWINDOW_H
