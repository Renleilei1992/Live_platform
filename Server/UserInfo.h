#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo          //主表类 只包含用户名和密码
{
private:
    int userID;
    QString userName;
    QString userPwd;

public:
    UserInfo();
    UserInfo(int userID, const QString& userName, const QString& userPwd);
    UserInfo(const QString& userName, const QString& userPwd);

    int get_userID()const {return userID;}
    const QString& getName()const {return userName;}
    const QString& getPwd()const {return userPwd;}
};

class UserIndex         //副表类 包含用户的各项信息，如消费金额、积分（将礼物换算为积分）、关注人数、用户名（与主表用户名一一对应）
{
private:
    int indexID;
    int consumption;
    int integration;
    int followers;
    QString indexName;

public:
    UserIndex();
    UserIndex(const QString& indexName);
    UserIndex(int indexID, int consumption, int integration, int followers, const QString& indexName);
    UserIndex(int consumption, int integration, int followers, const QString& indexName);

    int get_indexID()const {return indexID;}
    int get_consumption()const {return consumption;}
    int get_integration()const {return integration;}
    int get_followers()const {return followers;}
    const QString& get_indexName()const {return indexName;}
};

class RoomInfo
{
private:
    int roomID;
    QString roomName;           //房间名
    QString roomAddr;           //房间地址
    QString roomOwnerName;      //房间拥有者名字，作为数据库外键和基本信息中的名字绑定，一旦用户删除则直播间从数据库中也会删除

public:
    RoomInfo();
    RoomInfo(const QString& roomName);
    RoomInfo(int roomID, const QString& roomName,  const QString& roomAddr,const QString& roomOwnerName);
    RoomInfo(const QString& roomName,  const QString& roomAddr,const QString& roomOwnerName);

    int get_roomID(){ return roomID; }
    const QString& get_roomName()const { return roomName; }
    const QString& get_roomAddr()const { return roomAddr; }
    const QString& get_roomOwnerName()const { return roomOwnerName; }
};

#endif // USERINFO_H
