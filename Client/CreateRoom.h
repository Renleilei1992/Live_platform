#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QWidget>
#include <QString>
#include "Room.h"
#include "LiveWatch.h"
#include <QListWidgetItem>
#include <QMap>
#include <iostream>
using namespace std;

namespace Ui {
class CreateRoom;
}

class CreateRoom : public QWidget
{
    Q_OBJECT

public:
    Room *room;             //直播间对象
    LiveWatch *liveWatch;   //观看的直播间对象
    QMap<QString,QString> room_info_map;
    explicit CreateRoom(QWidget *parent = 0);
    ~CreateRoom();

private:
    Ui::CreateRoom *ui;
protected:
    void closeEvent(QCloseEvent *event);    //右上角关闭事件
signals:
    void open_createRoom_window(QString userName);  //打开创建直播间窗口信号（第二个窗口）（与主窗口通信）
    void open_mainWindow();                     //打开主窗口信号
    void open_create_room_window();             //打开创建直播间窗口信号（第二个窗口）（与第三个窗口通信）
    void open_room_window(QString roomName,QString roomAddr);//打开直播间窗口信号()(与主窗口通信)（信号发送至主窗口）
    void check_room_info2();                    //查询在线直播间名字和地址信号(发送至主窗口)
    void quit_room(QString room_name);          //房间关闭信号，由第二窗口发出，主窗口接收
    void enter_live_userName(QString userName,QString roomName); //进入观看直播，由第二窗口发出，主窗口接收（发送至服务器用以刷新在线用户列表）
    void quit_live_userName(QString userName,QString roomName);  //退出观看直播后，由第二窗口发出，主窗口接收（发送至服务器用以刷新在线用户列表）
    void quit_back_infoFromServer_userName(QString quitLiveName);//退出观看直播用户名，由第二个窗口发出，直播间接收
    void send_barrage_toServer(QString msgContent,QString roomName);//直播间弹幕内容，由第二窗口发出，主窗口接收（发送至服务器）
    void online_userName(QString onlineUserName,int flagNum);//直播间在线用户名，由第二窗口发出，直播间窗口接收
    void signal_barrage_backFromServer(QString barrageBack);//从服务器返回的弹幕内容，由第二窗口发出，直播间接收
    void offline_Info(QString offline_userName);            //用户离线信号，由第二窗口发出，主窗口接收，（发送至服务器）

private slots:
    void on_btn_return_clicked();           //返回主界面槽函数（与第二个窗口通信）
    void on_btn_createRoom_clicked();       //创建房间按钮槽函数（与第二个窗口通信）
    void open_create_window_slot();         //打开创建直播间槽函数(与第二个窗口通信)（接收的信号来自直播间窗口）
    void open_room_window_slot();           //打开直播间窗口槽函数(与主窗口通信)（接收的信号来自主窗口）
    void check_room_info_slot(QString room_name,QString room_addr);//查询在线房间信息槽函数(与主窗口通信)（接收的信号来自主窗口）
    void on_btn_refresh_clicked();          //刷新查询在线房间列表
    void on_list_roomList_itemDoubleClicked(QListWidgetItem *item);//双击房间列表的槽函数
    void quit_live_slot();                  //退出观看直播间槽函数（信号来自直播间）
    void quit_back_infoFromServer_slot(QString quitLiveUserName);//退出观看直播间槽函数（信号来自主窗口，来自服务器，包含退出房间用户名）
    void send_barrage_slot(QString msg,QString roomName);//直播间弹幕接收槽函数（信号来自直播间窗口）
    void online_user_inLiveRoom_slot(QString onlineUserName,int flagNum);//直播间在线用户名（信号来自主窗口）
    void signal_barrage_back_slot(QString barrage_back);     //服务器返回的弹幕信息处理槽函数（信号来自主窗口）
};

#endif // CREATEROOM_H
