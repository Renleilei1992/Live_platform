#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "protocol.h"
#include <Qt>
#include <QLineEdit>
#include <QDebug>
#include <string>
#include <iostream>
#include <cstdlib>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "TempData.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);

    socket = new QTcpSocket(this);
//    socket->connectToHost(QHostAddress("192.168.10.12"),8888);
    socket->connectToHost(QHostAddress::LocalHost,8888);

    connect(socket, SIGNAL(readyRead()),
            this, SLOT(readyReadSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_register_clicked()
{
    string user_name_register = ui->lineEdit_name->text().toStdString();
    string user_pwd_register = ui->lineEdit_pwd->text().toStdString();
    qDebug()<<user_name_register.data();
    qDebug()<<user_pwd_register.data();

    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));       //初始化数据包,注意数据包赋值在初始化之后进行
    package_send.type = REG_INFO;                   //数据包类型为注册
    user_name_register.copy(package_send.userName,user_name_register.size(),0);
    user_pwd_register.copy(package_send.userPwd,user_pwd_register.size(),0);
    qDebug()<<package_send.userName;
    qDebug()<<package_send.userPwd;

    socket->write((const char*)&package_send, sizeof(package_send));
}

void MainWindow::on_btn_login_clicked()
{
    string user_name_login = ui->lineEdit_name->text().toStdString();
    string user_pwd_login = ui->lineEdit_pwd->text().toStdString();
    qDebug()<<user_name_login.data();
    qDebug()<<user_pwd_login.data();
    TempData::room_owner_name = ui->lineEdit_name->text();      //登录时输入的登录名记录到全局变量中（若登录不成功会清除）

    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));       //初始化数据包，注意加入数据在初始化之后
    package_send.type = LOG_INFO;                   //数据包类型为登录
    user_name_login.copy(package_send.userName,user_name_login.size(),0);
    user_pwd_login.copy(package_send.userPwd,user_pwd_login.size(),0);
    qDebug()<<package_send.userName;
    qDebug()<<package_send.userPwd;

    socket->write((const char*)&package_send, sizeof(package_send));
}

void MainWindow::readyReadSlot()
{
    Protocol package_back;
    memset(&package_back, 0, sizeof(package_back));

    while(socket->read((char*)&package_back, sizeof(package_back)) > 0){
        switch(package_back.type){
            case REG_FAIL:
                QMessageBox::warning(this, "注册信息","注册失败");
                break;
            case REG_SUCCESSFUL:
                QMessageBox::information(this, "注册信息","注册成功");
                break;
            case LOG_FAIL:
                QMessageBox::warning(this,"登录信息","用户名或密码错误");
                TempData::room_owner_name = "0";
                break;
            case LOG_SUCCESSFUL:
                QMessageBox::information(this,"登录信息","登录成功，欢迎！");
//                emit open_createRoom_window(package_back.userName);
                open_createRoom_window_slot(package_back.userName);
                qDebug()<<"log success userName: "<<package_back.userName;
                TempData::user_name = package_back.userName;
                break;
            case CREATE_FAIL:
                QMessageBox::warning(this, "创建信息","创建失败");
                break;
            case CREATE_SUCCESSFUL:
                QMessageBox::information(this, "创建信息","创建成功");
                qDebug()<<"rcv CREATE_BACK success! "<<package_back.roomAddr;
                TempData::room_addr = package_back.roomAddr;
                emit open_room_window_success();        //接收到服务器返回的创建成功信息后发出该信号，槽函数创建出直播间窗口
                break;
            case CHECK_BACK:
                qDebug()<<"rcv CHECK_BACK success!"<<package_back.roomName<<" "<<package_back.roomAddr;
                emit check_room_info(package_back.roomName,package_back.roomAddr);//接收到服务器传递回的房间名和地址信息
                break;
            case QUIT_BACK:
                qDebug()<<"rcv QUIT_BACK success!"<<package_back.userName;
                emit quit_back_infoFromServer(package_back.userName);//接收到服务器传递回的用户离开直播间信息
                break;
            case REFRESH_BACK:
                qDebug()<<"rcv RFRESH_BACK success! onlineUserName: "<<package_back.userName<<"flag: "<<package_back.flag;
                emit online_user_inLiveRoom(package_back.userName,package_back.flag);//接收到服务器传递回的直播间在线用户名
                break;
            case DANMU_BACK:
                qDebug()<<"rcv DANMU_BACK success! "<<package_back.barrage;
                emit signal_barrage_back(package_back.barrage);
                break;
            default:
                qDebug()<<"default type: "<<package_back.type<<" "<<package_back.roomName;
//                QMessageBox::warning(this,"提示信息","未知错误，请重新启动程序！");
                break;
        }
    }
}

//生成第二个窗口的槽函数
void MainWindow::open_createRoom_window_slot(QString userName)
{
    createRoom = new CreateRoom();                      //创建出第二个窗口的对象指针

    this->hide();
    createRoom->show();

    connect(createRoom, SIGNAL(open_mainWindow()),
            this, SLOT(show()));
    connect(createRoom, SIGNAL(open_room_window(QString,QString)),
            this, SLOT(create_room_window_slot(QString,QString))); //接收创建窗口的信号(包含房间名和地址)，由主窗口写入套接字
    connect(this, SIGNAL(open_room_window_success()),
            createRoom, SLOT(open_room_window_slot())); //服务器返回 创建成功 就发出信号然后接收，槽函数位于创建窗口
    connect(this, SIGNAL(check_room_info(QString,QString)),
            createRoom, SLOT(check_room_info_slot(QString,QString)));//服务器返回 查询房间信息结果 发出信号第二窗口接收并显示
    connect(createRoom, SIGNAL(check_room_info2()),
            this, SLOT(check_room_info2_slot()));   //接收第二个窗口的查询（刷新）信号并向服务器发送查询请求
    connect(createRoom, SIGNAL(quit_room(QString)),
            this, SLOT(quit_room_slot(QString)));   //接收第二个窗口的退出（其实来自于直播间窗口）信号并向服务器发送退出请求
    connect(createRoom, SIGNAL(enter_live_userName(QString,QString)),
            this, SLOT(enter_live_userName_slot(QString,QString)));//接收第二个窗口的进入（来自于观看直播间窗口进入）信号并向服务器发送
    connect(createRoom, SIGNAL(quit_live_userName(QString,QString)),
            this, SLOT(quit_live_userName_slot(QString,QString)));//接收第二个窗口的退出（来自于观看直播间窗口退出）信号并向服务器发送
    connect(createRoom, SIGNAL(send_barrage_toServer(QString,QString)),
            this, SLOT(send_barrage_toServer_slot(QString,QString)));//接收第二个窗口的弹幕（来自于直播间）信号并向服务器发送
    connect(this, SIGNAL(online_user_inLiveRoom(QString,int)),
            createRoom, SLOT(online_user_inLiveRoom_slot(QString,int)));//服务器返回直播间在线用户名，向第二个窗口发送信息
    connect(this, SIGNAL(signal_barrage_back(QString)),
            createRoom, SLOT(signal_barrage_back_slot(QString)));   //服务器返回的弹幕内容，向第二个窗口发送信息
    connect(this, SIGNAL(quit_back_infoFromServer(QString)),
            createRoom, SLOT(quit_back_infoFromServer_slot(QString)));//服务器返回的离开用户名，向第二个窗口发送信息
    connect(createRoom, SIGNAL(offline_Info(QString)),
            this, SLOT(offline_Info_slot(QString)));                //接收来自第二窗口的用户离线信息，向服务器发送离线信息

}

//接收创建房间信号并传递信息到服务器写入数据库槽函数
void MainWindow::create_room_window_slot(QString roomName,QString roomAddr)
{
    string roomOwner_create = TempData::room_owner_name.toStdString();
    string roomName_create = roomName.toStdString();
    string roomAddr_create = roomAddr.toStdString();
    qDebug()<<roomName_create.data();               //string类型需要调用.data()函数来打印在终端，不同于QString类型
    qDebug()<<roomAddr_create.data();

    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));       //初始化数据包，注意加入数据在初始化之后
    package_send.type = CREATE_INFO;                //数据包类型为创建房间
    roomOwner_create.copy(package_send.userName,roomOwner_create.size(),0);
    roomName_create.copy(package_send.roomName,roomName_create.size(),0);
    roomAddr_create.copy(package_send.roomAddr,roomAddr_create.size(),0);
    qDebug()<<package_send.userName<<" package success!";
    qDebug()<<package_send.roomName<<" package success!";
    qDebug()<<package_send.roomAddr<<" package success!";

    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送查询已打开的直播间名字的请求到服务器的槽函数
void MainWindow::check_room_info2_slot()
{
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = CHECK_INFO;

    qDebug()<<"CHECK_INFO package success!";
    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送关闭直播间的房间名到服务器的槽函数
void MainWindow::quit_room_slot(QString room_name)
{
    string quit_room_name = room_name.toStdString();
    string quit_user_name = TempData::user_name.toStdString();
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = QUIT_ROOM;
    quit_room_name.copy(package_send.roomName,quit_room_name.size(),0);
    quit_user_name.copy(package_send.userName,quit_user_name.size(),0);
    qDebug()<<"quit package send success! quit room name: "<<room_name;
    qDebug()<<"quit package send success! quit user name: "<<TempData::user_name;

    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送进入直播间用户名到服务器的槽函数
void MainWindow::enter_live_userName_slot(QString userName, QString roomName)
{
    string enter_live_userName = userName.toStdString();
    string enter_live_roomName = roomName.toStdString();
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = ENTER_LIVE;
    enter_live_userName.copy(package_send.userName,enter_live_userName.size(),0);
    enter_live_roomName.copy(package_send.roomName,enter_live_roomName.size(),0);
    qDebug()<<"enter live package send success! enter live userName: "<<userName;
    qDebug()<<"enter live package send success! enter live userName: "<<roomName;

    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送退出直播间用户名到服务器的槽函数
void MainWindow::quit_live_userName_slot(QString userName, QString roomName)
{
    string quit_live_userName = userName.toStdString();
    string quit_live_roomName = roomName.toStdString();
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = QUIT_LIVE;
    quit_live_userName.copy(package_send.userName,quit_live_userName.size(),0);
    quit_live_roomName.copy(package_send.roomName,quit_live_roomName.size(),0);
    qDebug()<<"quit live package send success! quit live userName: "<<userName;
    qDebug()<<"quit live package send success! quit live roomName: "<<roomName;

    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送弹幕内容和直播间名字到服务器
void MainWindow::send_barrage_toServer_slot(QString msgContent, QString roomName)
{
    string send_barrage_content = msgContent.toStdString();
    string send_barrage_roomName = roomName.toStdString();
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = DANMU_INFO;
    send_barrage_content.copy(package_send.barrage,send_barrage_content.size(),0);
    send_barrage_roomName.copy(package_send.roomName,send_barrage_roomName.size(),0);
    qDebug()<<"barrage package send success! barrage content: "<<msgContent;
    qDebug()<<"barrage package send success! barrage roomName: "<<roomName;

    socket->write((const char*)&package_send, sizeof(package_send));
}

//发送某用户离线信息到服务器(目的用于清除服务器在线用户数据库信息)
void MainWindow::offline_Info_slot(QString offline_userName)
{
    string send_offline_userName = offline_userName.toStdString();
    Protocol package_send;
    memset(&package_send,0,sizeof(Protocol));
    package_send.type = OFFLINE_INFO;
    send_offline_userName.copy(package_send.userName,send_offline_userName.size(),0);
    qDebug()<<"offline package send success! offline_userName: "<<offline_userName;

    socket->write((const char*)&package_send, sizeof(package_send));
}
