#include "CreateRoom.h"
#include "ui_CreateRoom.h"
#include <QDebug>
#include "TempData.h"
#include <QMap>
#include <QMessageBox>

CreateRoom::CreateRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateRoom)
{
    ui->setupUi(this);
    qDebug()<<"window 2";

    ui->label_userName->setText(TempData::room_owner_name); //通过静态全局变量修改房主名字


    //指针创建位置改在之后可以读取到静态全局变量的值
//    room = new Room();      //创建出直播间的对象指针
//    connect(room,SIGNAL(open_create_window()),
//            this,SLOT(open_create_window_slot()));

}

CreateRoom::~CreateRoom()
{
    delete ui;
}


//当这个按钮点击后会触发:创建UDP广播并往主窗口发送房间名及广播地址信号
//                   将房间名写入静态全局变量（全局变量需在切换账号时恢复！！）
//                   创建一个直播间对象并加以连接
void CreateRoom::on_btn_createRoom_clicked()
{
    QString room_name_tmp = ui->line_roomName->text();
    QString room_introduce_tmp = ui->text_introduce->toPlainText();

    ui->line_roomName->clear();
    ui->text_introduce->clear();

    qDebug()<<"room name :"<<room_name_tmp;
    qDebug()<<"room intro:"<<room_introduce_tmp;

    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    int n = qrand()%254;
    int p = qrand()%188;
    int k = qrand()%199;

    QString room_Addr_tmp = "224.";        //由于未创建UDP，先使用默认的广播地址(可以使用TempData传递该地址，暂时自定义)
    room_Addr_tmp += QString::number(n);
    room_Addr_tmp += ".";
    room_Addr_tmp += QString::number(p);
    room_Addr_tmp += ".";
    room_Addr_tmp += QString::number(k);
    qDebug()<<" 随机数生成的地址: "<<room_Addr_tmp;

    emit open_room_window(room_name_tmp, room_Addr_tmp);   //准备数据包新建一个类型为直播间信息，传递到主线程写入套接字
    TempData::room_name = room_name_tmp;
    TempData::room_introduce = room_introduce_tmp;

    qDebug()<<"room name :"<<TempData::room_name;
    qDebug()<<"room intro:"<<TempData::room_introduce;

    room = new Room();      //创建出直播间的对象指针
    connect(room, SIGNAL(open_create_window()),
            this, SLOT(open_create_window_slot()));
    connect(room, SIGNAL(send_barrage(QString,QString)),
            this, SLOT(send_barrage_slot(QString,QString)));//接收直播间弹幕内容及房间名连接
    connect(this, SIGNAL(online_userName(QString,int)),
            room, SLOT(online_userName_slot(QString,int)));//接收主窗口传来的直播间在线用户信号，发送至直播间窗口接收
    connect(this, SIGNAL(signal_barrage_backFromServer(QString)),
            room, SLOT(signal_barrage_backFromServer_slot(QString)));//服务器发回的弹幕内容发至直播间窗口接收
    connect(this, SIGNAL(quit_back_infoFromServer_userName(QString)),
            room, SLOT(quit_userName_slot(QString)));  //将服务器返回的退出直播间的用户名打印在弹幕区
    ui->list_roomList->clear();

}

void CreateRoom::open_room_window_slot()        //打开直播间窗口槽函数，信号由主窗口发出主窗口接收创建窗口执行
{
    this->hide();
    room->show();
}

void CreateRoom::open_create_window_slot()      //打开第二个窗口槽函数
{
    emit quit_room(TempData::room_name);
    this->show();                   //接收到直播间关闭信号后此窗口打开()
//    delete room;
}

void CreateRoom::on_btn_return_clicked()
{
    emit open_mainWindow();
    emit offline_Info(TempData::user_name);     //点击返回按钮时向主窗口发送用户下线信息
    this->close();
//    delete room;
}

void CreateRoom::check_room_info_slot(QString room_name,QString room_addr)
{
    room_info_map.insert(room_name,room_addr);    //每接收到一个在线房间名即插入map容器中
    ui->list_roomList->addItem(room_name);
}

//通过刷新按钮向服务器请求在线房间名以及房间UDP地址
void CreateRoom::on_btn_refresh_clicked()
{
    ui->list_roomList->clear();
    room_info_map.clear();    //清空全局变量的map数据
    emit check_room_info2();
}

void CreateRoom::on_list_roomList_itemDoubleClicked(QListWidgetItem *item)
{
    QString room_name_item = item->text();
    QMap<QString,QString>::iterator it = room_info_map.find(room_name_item);
    QString room_addr = it.value().section(',',0,0).trimmed();
    QString room_ownerName = it.value().section(',',1,1).trimmed();

    qDebug()<<"The roomNam is: "<<it.key();
    qDebug()<<"The address is: "<<room_addr;
    qDebug()<<"The roomOwnerName is: "<<room_ownerName;
    TempData::room_name = it.key();
    TempData::room_addr = room_addr;
    TempData::room_ownerName = room_ownerName;
//    TempData::user_name = ui->label_userName->text();

    emit enter_live_userName(TempData::user_name, TempData::room_name);

    liveWatch = new LiveWatch();
    connect(liveWatch, SIGNAL(quit_live()),
            this, SLOT(quit_live_slot()));   //接收观看直播间的退出信号
    connect(liveWatch, SIGNAL(send_barrage(QString,QString)),
            this, SLOT(send_barrage_slot(QString,QString)));
    connect(this, SIGNAL(online_userName(QString,int)),
            liveWatch, SLOT(online_userName_slot_live(QString,int)));//接收主窗口传来的直播间在线用户信号，发送至直播间窗口接收
    connect(this, SIGNAL(signal_barrage_backFromServer(QString)),
            liveWatch, SLOT(signal_barrage_backFromServer_slot(QString)));//将服务器发送回的弹幕内容连接发送至直播间
    connect(this, SIGNAL(quit_back_infoFromServer_userName(QString)),
            liveWatch, SLOT(quit_userName_slot(QString)));  //将服务器返回的退出直播间的用户名打印在弹幕区
    this->hide();
    liveWatch->show();
}

void CreateRoom::quit_live_slot()
{
    this->show();
    emit quit_live_userName(TempData::user_name, TempData::room_name);
}

void CreateRoom::quit_back_infoFromServer_slot(QString quitLiveUserName)
{
    emit quit_back_infoFromServer_userName(quitLiveUserName);
}

void CreateRoom::send_barrage_slot(QString msg, QString roomName)
{
    emit send_barrage_toServer(msg,roomName);   //向主窗口发送弹幕内容的槽函数，信号来自直播间
}

void CreateRoom::online_user_inLiveRoom_slot(QString onlineUserName,int flagNum)
{
    emit online_userName(onlineUserName,flagNum);//接收到主窗口的在线用户名信号，发送至直播间窗口
}

void CreateRoom::signal_barrage_back_slot(QString barrage_back)
{
    emit signal_barrage_backFromServer(barrage_back);//接收到主窗口返回的来自服务器的弹幕内容，发送至直播间窗口
}

//右上角关闭按钮事件处理，对其处理为 功能和返回按钮一致
void CreateRoom::closeEvent(QCloseEvent *event)   //将窗口右上角的关闭按钮事件功能做成和quit按钮一致
{
    emit offline_Info(TempData::user_name);     //点击右上角X按钮时向主窗口发送用户下线信息
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("警告：程序有一个任务正在运行中，是否结束操作退出?")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }else if(button == QMessageBox::Yes){
        event->accept();  //接受退出信号，程序退出
    }
}
