#include "UserInfo.h"

UserInfo::UserInfo()
{

}

UserInfo::UserInfo(int userID, const QString& userName, const QString& userPwd)
    :userID(userID),userName(userName),userPwd(userPwd)
{

}

UserInfo::UserInfo(const QString& userName, const QString& userPwd)
    :userName(userName),userPwd(userPwd)
{

}


UserIndex::UserIndex()
{

}

UserIndex::UserIndex(const QString &indexName)
    :indexName(indexName)
{

}

UserIndex::UserIndex(int indexID, int consumption, int integration, int followers, const QString& indexName)
    :indexID(indexID),consumption(consumption),integration(integration),followers(followers),indexName(indexName)
{

}

UserIndex::UserIndex(int consumption, int integration, int followers, const QString& indexName)
    :consumption(consumption),integration(integration),followers(followers),indexName(indexName)
{

}


RoomInfo::RoomInfo()
{

}

RoomInfo::RoomInfo(const QString &roomName)
    :roomName(roomName)
{

}

RoomInfo::RoomInfo(int roomID, const QString& roomName,  const QString& roomAddr,const QString& roomOwnerName)
    :roomID(roomID),roomName(roomName),roomAddr(roomAddr),roomOwnerName(roomOwnerName)
{

}

RoomInfo::RoomInfo(const QString& roomName,  const QString& roomAddr,const QString& roomOwnerName)
    :roomName(roomName),roomAddr(roomAddr),roomOwnerName(roomOwnerName)
{

}
