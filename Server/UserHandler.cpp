#include "UserHandler.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "DBHelper.h"

UserHandler::UserHandler()
{

}

//注册的时候向数据库中写入用户基本信息，包括账户名及用户密码
bool UserHandler::insertUser(const UserInfo& userInfo)
{
    DBHelper *instance = DBHelper::getInstance();
    instance->createConnection();       //建立与数据库的链接

    QSqlQuery query_info;
    query_info.prepare("insert into userInfo(userName,userPwd)values(:userName, :userPwd);");
    query_info.bindValue(":userName",userInfo.getName());
    query_info.bindValue(":userPwd",userInfo.getPwd());
    qDebug()<<query_info.lastError()<<"flag insert info";

    bool ret_info = query_info.exec();          //执行插入基本信息
    if(!ret_info){
        qDebug()<<query_info.lastError();
    }

    instance->removeConnection();
    return ret_info;
}

//登录的时候需要往数据库中写入用户次要信息，如果写入失败证明该用户已登录！
bool UserHandler::inserUserOL(const UserIndex& userIndex)
{
    DBHelper *instance = DBHelper::getInstance();
    instance->createConnection();       //建立与数据库的链接

    QSqlQuery query_index;
    query_index.prepare("insert into userOL(userName)values(:userName);");
    query_index.bindValue(":userName",userIndex.get_indexName());
    qDebug()<<query_index.lastError()<<"flag insert index";

    bool ret_index = query_index.exec();        //执行插入附加信息
    if(!ret_index){
        qDebug()<<query_index.lastError();
    }

    instance->removeConnection();
    return ret_index;
}

//插入直播间信息到数据库中
bool UserHandler::insertRoom(const RoomInfo &roomInfo)
{
    DBHelper *instance = DBHelper::getInstance();
    instance->createConnection();

    QSqlQuery query_room;
    query_room.prepare("insert into roomInfo(roomName,roomAddr,roomOwnerName)"
                       "values(:roomName,:roomAddr,:roomOwnerName);");
    query_room.bindValue(":roomName",roomInfo.get_roomName());
    query_room.bindValue(":roomAddr",roomInfo.get_roomAddr());
    query_room.bindValue(":roomOwnerName",roomInfo.get_roomOwnerName());

    bool ret_createRoom = query_room.exec();
    if(!ret_createRoom){
        qDebug()<<query_room.lastError();
    }

    instance->removeConnection();
    return ret_createRoom;
}

bool UserHandler::deleteRoom(const RoomInfo &roomInfo)
{
    qDebug()<<"Quit room name: "<<roomInfo.get_roomName();
    DBHelper *instance = DBHelper::getInstance();
    instance->createConnection();

    QSqlQuery query_quit;
    query_quit.prepare("delete from roomInfo where roomName=:roomName;");
    query_quit.bindValue(":roomName",roomInfo.get_roomName());

    bool ret_quit = query_quit.exec();
    if(!ret_quit){
        qDebug()<<query_quit.lastError()<<"quit delete flag!";
    }

    instance->removeConnection();
    return ret_quit;
}

bool UserHandler::deleteUserOL(const UserInfo &userInfo)
{
    qDebug()<<"Offline user name: "<<userInfo.getName();
    DBHelper *instance = DBHelper::getInstance();
    instance->createConnection();

    QSqlQuery query_offline;
    query_offline.prepare("delete from userOL where userName=:userName;");
    query_offline.bindValue(":userName",userInfo.getName());

    bool ret_offline = query_offline.exec();
    if(!ret_offline){
        qDebug()<<query_offline.lastError()<<"offline delete flag!";
    }

    instance->removeConnection();
    return ret_offline;
}

QString UserHandler::checkPwd(QString name_check)
{
    qDebug()<<"Check password user_name: "<<name_check;
    DBHelper* instance = DBHelper::getInstance();
    instance->createConnection();

    QSqlQuery query;
    QString pwd_check;
    query.prepare("select userPwd from userInfo where userName=:userName;");
    query.bindValue(":userName",name_check);

    bool ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError()<<"check flag";
    }

    while(query.next()){
        pwd_check = query.value(0).toString();
    }

    instance->removeConnection();
    qDebug()<<"Check password of user_name: "<<name_check<<" password: "<<pwd_check;
    return pwd_check;
}

QMap<QString,QString> UserHandler::checkOnlineRoom()
{
    qDebug()<<"check online room name and address!";
    DBHelper* instance = DBHelper::getInstance();
    instance->createConnection();

    QSqlQuery query_checkOnline;
    QMap<QString,QString> onlineRoom_map;
    QString check_room_name,check_room_addr,check_room_owner,check_room_back;
    query_checkOnline.prepare("select roomName,roomAddr,roomOwnerName from roomInfo where roomID>1;");
    bool ret_checkOnlineRoom = query_checkOnline.exec();
    if(!ret_checkOnlineRoom){
        qDebug()<<query_checkOnline.lastError()<<"checkOnlineRoom flag";
    }

    while(query_checkOnline.next()){
        check_room_name = query_checkOnline.value(0).toString();
        check_room_addr = query_checkOnline.value(1).toString();
        check_room_owner = query_checkOnline.value(2).toString();
        check_room_back = check_room_addr;
        check_room_back += ",";
        check_room_back += check_room_owner;
        qDebug()<<check_room_back<<" 字符串拼接处结果！";

        onlineRoom_map.insert(check_room_name,check_room_back);     //将查询到的房间名和地址以键值对的形式存储在map中
    }

    instance->removeConnection();
    qDebug()<<"checkOnlineRoom success!";
    return onlineRoom_map;
}

