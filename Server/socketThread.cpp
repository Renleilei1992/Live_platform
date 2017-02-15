#include "socketThread.h"
#include <QTcpSocket>
#include <QDebug>
#include "UserHandler.h"
#include "UserInfo.h"
#include "NetWorkManager.h"

SocketThread::SocketThread(QTcpSocket *socket, QObject *parent)
    : socket(socket),
      QObject(parent)
{
    //当有套接字动作的时候会触发readyRead信号
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(ready_read_slot()));
}

void SocketThread::ready_read_slot()
{
    Protocol package_user;
    memset(&package_user, 0, sizeof(package_user));

    while(socket->read((char*)&package_user,
                       sizeof(package_user)) > 0)
    {
        switch (package_user.type) {
        case REG_INFO:
            qDebug()<<"rcv register!";
            qDebug()<<"register username: "<<package_user.userName;
            qDebug()<<"register password: "<<package_user.userPwd;
            this->register_user(&package_user);
            break;
        case LOG_INFO:
            qDebug()<<"rcv login!";
            qDebug()<<"login username: "<<package_user.userName;
            qDebug()<<"login password: "<<package_user.userPwd;
            this->login_user(&package_user);
            this->check_online_room(&package_user);
            break;
        case CREATE_INFO:
            qDebug()<<"rcv create room msg!";
            qDebug()<<"userName: "<<package_user.userName;
            qDebug()<<"roomName: "<<package_user.roomName;
            qDebug()<<"roomAddr: "<<package_user.roomAddr;
            this->create_room(&package_user);   //接收到创建房间的套接字信息，调用创建房间函数处理（存入数据库）
            break;
        case CHECK_INFO:
            qDebug()<<"rcv check room msg!";
            this->check_online_room(&package_user);
            break;
        case QUIT_ROOM:
            qDebug()<<"rcv quit room information!"<<package_user.roomName;
            this->quit_room(&package_user);//接收到直播间退出的套接字信息，调用退出房间函数处理（删除数据库中数据）
            emit signal_quitRoom(socket,package_user.roomName,package_user.userName);//关闭直播间即向主线程发送信号
            break;
        case ENTER_LIVE:
            qDebug()<<"somebody enter the liveRoom! userName:"<<package_user.userName;
            qDebug()<<"somebody enter the liveRoom! roomName:"<<package_user.roomName;
            emit signal_enterLiveRoom(socket,package_user.roomName,package_user.userName);//进入直播间即向主线程发送信号
            break;
        case QUIT_LIVE:
            qDebug()<<"somebody quit the liveRoom! userName:"<<package_user.userName;
            qDebug()<<"somebody quit the liveRoom! roomName:"<<package_user.roomName;
            emit signal_quitLiveRoom(socket,package_user.roomName,package_user.userName);//离开直播间即向主线程发送信号
            break;
        case DANMU_INFO:
            qDebug()<<"rcv DANUMU_INFO message:"<<package_user.barrage<<" roomName: "<<package_user.roomName;
            emit signal_barrage(package_user.roomName,package_user.barrage);//接收到客户端的弹幕信息向主线程发送信号
            break;
        case OFFLINE_INFO:
            qDebug()<<"rcv OFFLINE_INFO message:"<<package_user.userName;
            this->offline_handle(&package_user);//接收到客户端用户的离线信息，刷新数据库
            break;
        default:
            qDebug()<<"no type rcv!";
            break;
        }
    }
}

void SocketThread::sleep_diy(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

//线程处理用户注册事件
void SocketThread::register_user(Protocol* package_user_register)
{
    QString register_userName = package_user_register->userName;
    QString register_userPwd = package_user_register->userPwd;

    UserInfo user_information(register_userName, register_userPwd);
    UserHandler* user_handler = new UserHandler();

    //在数据库中查询该用户名是否存在密码，若有密码则该用户名已注册，反之则未注册
    QString pwd_check;
    pwd_check = user_handler->checkPwd(register_userName);
    if(pwd_check != 0){
        qDebug()<<"The user name is existed! Regist failed!";
        package_user_register->type = REG_FAIL;                 //宏更改为失败
    }else{
        package_user_register->type = REG_SUCCESSFUL;           //宏更改为成功
        user_handler->insertUser(user_information);             //向数据库中插入该用户
        qDebug()<<"Regist success!" ;
    }
    emit signal_message(socket,
                        (const char*)package_user_register,
                        sizeof(*package_user_register));
    delete user_handler;
}

//线程处理用户登录事件
void SocketThread::login_user(Protocol* package_user_login)
{
    QString login_userName = package_user_login->userName;
    QString login_userPwd = package_user_login->userPwd;
    qDebug()<<"Check password login_userName: "<<login_userName<<" inThread!";

    UserHandler* user_handler = new UserHandler();

    //在数据库中查询该用户名密码是否与登录密码匹配
    QString pwd_check;
    pwd_check = user_handler->checkPwd(login_userName);

    if(pwd_check == login_userPwd){
        qDebug()<<"pwd correct!";
        UserIndex user_index(login_userName);
        bool ret_index = user_handler->inserUserOL(user_index);
        if(ret_index){
            qDebug()<<"LOGIN success!";
            package_user_login->type = LOG_SUCCESSFUL;
        }else{
            qDebug()<<"You are already OL!";
            package_user_login->type = LOG_FAIL;
        }
    }else{
        qDebug()<<"Password wrong or the user name is Non-existent!";
        package_user_login->type = LOG_FAIL;
    }

    emit signal_message(socket, (const char*)package_user_login, sizeof(*package_user_login));
    delete user_handler;
}

//线程处理创建直播间事件
void SocketThread::create_room(Protocol *package_user_create)
{
    QString room_owner_name = package_user_create->userName;
    QString room_name = package_user_create->roomName;
    QString room_addr = package_user_create->roomAddr;

    RoomInfo room_infomation(room_name,room_addr,room_owner_name);
    UserHandler* user_handler = new UserHandler();
    bool ret_create = user_handler->insertRoom(room_infomation);
    if(!ret_create){
        qDebug()<<"create failed!";
        package_user_create->type = CREATE_FAIL;
    }else{
        qDebug()<<"create success!";
        package_user_create->type = CREATE_SUCCESSFUL;
        emit signal_room_info(socket,room_name,room_owner_name);//向主线程发送房间信息
    }

    emit signal_message(socket,(const char*)package_user_create,sizeof(*package_user_create));
    delete user_handler;

    sleep_diy(1000);
    emit signal_refresh_onlineUser(socket, room_name);
}

//线程处理 查询在线房间信息事件
void SocketThread::check_online_room(Protocol *package_user_check)
{
    string check_roomName,check_roomAddr;
    UserHandler* user_handler = new UserHandler();
    QMap<QString,QString> check_online_map;             //创建map容器用以接收数据库查询出的数据
    QMap<QString,QString>::iterator it;                 //创建迭代器用以遍历map容器
    check_online_map = user_handler->checkOnlineRoom();

//    Protocol package_sendBack;

    for(it = check_online_map.begin(); it != check_online_map.end(); ++it)
    {
        check_roomName = it.key().toStdString();            //格式转换由QString->string->char
        check_roomAddr = it.value().toStdString();
        qDebug()<<"check online FLAG-1! roomName:"<<it.key()<<" roomAddr:"<<it.value();
        memset(package_user_check,0,sizeof(Protocol));
        package_user_check->type = CHECK_BACK;
        check_roomName.copy(package_user_check->roomName,check_roomName.size(),0);
        check_roomAddr.copy(package_user_check->roomAddr,check_roomAddr.size(),0);

        emit signal_message(socket,(const char*)package_user_check,sizeof(*package_user_check));
        sleep_diy(10);
    }
    delete user_handler;
}

void SocketThread::quit_room(Protocol* package_user_quit)
{
    QString quit_room_name = package_user_quit->roomName;
    UserHandler* user_handler = new UserHandler();
    RoomInfo quit_room_info(quit_room_name);

    bool ret_quit = user_handler->deleteRoom(quit_room_info);
    if(ret_quit){
        qDebug()<<"delete success!";
        package_user_quit->type = QUIT_BACK;
    }else{
        qDebug()<<"delete failed!";
        package_user_quit->type = QUIT_BACK;
    }

    emit signal_message(socket,(const char*)package_user_quit,sizeof(*package_user_quit));
    delete user_handler;
}

void SocketThread::offline_handle(Protocol *package_user_offline)
{
    QString offline_userName = package_user_offline->userName;
    QString offline_pwd_tmp = "tmp_pwd";    //由于构造方法需要密码，下线时临时使用一个构造元素
    UserHandler* user_handler = new UserHandler();
    UserInfo user_offline(offline_userName,offline_pwd_tmp);

    bool ret_offline = user_handler->deleteUserOL(user_offline);
    if(ret_offline){
        qDebug()<<"delete success! -OFFline flag!";
    }else{
        qDebug()<<"delete failed! -OFFline flag!";
    }

    delete user_handler;
}
