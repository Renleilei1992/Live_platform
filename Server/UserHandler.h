#ifndef USERHANDLER_H
#define USERHANDLER_H

#include "UserInfo.h"
#include <QMap>
#include <iostream>
using namespace std;

class UserHandler
{
public:
    UserHandler();
    bool insertUser(const UserInfo& userInfo);      //向数据库中插入用户基本信息（账号密码）
    bool insertRoom(const RoomInfo& roomInfo);      //向数据库中插入新开的直播间信息用以刷新直播间列表（退出直播间将删除）
    bool deleteRoom(const RoomInfo& roomInfo);      //当接收到客户端关闭直播间信息后删除数据库中该直播间信息
    bool inserUserOL(const UserIndex& userIndex);   //用户登陆时，向数据库中插入该用户的次要信息（成功即上线，失败即上线失败，即数据库中已存在该在线用户）
    bool deleteUserOL(const UserInfo& userInfo);    //用户离线时，从数据库中删除该用户的信息
    QString checkPwd(QString name_check);           //在数据库中查询用户基本信息
    QMap<QString,QString> checkOnlineRoom();        //在数据库中查询在线房间名字及地址，使用QMap接收键值对

//    bool selectUser(const UserInfo& UserInfo);
};

#endif // USERHANDLER_H
