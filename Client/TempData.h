#ifndef TEMPDATA_H
#define TEMPDATA_H

#include <QString>

//客户端全局变量类，主要用以传递创建直播间的名字和直播间简介等内容

class TempData
{
public:
    static QString room_owner_name; //(登陆者)房间拥有者信息，由主窗口更改
    static QString room_name;       //直播间名字，1，第二窗口在创建时即更改
    static QString room_introduce;
    static QString room_addr;
    static QString user_name;
    static bool check_video;
    static bool check_sound;
    static QString room_ownerName;  //(观看的直播间房主)，由服务器返回信息后更改，第二窗口


public:
    TempData();
    ~TempData();
//    TempData(const QString& room_name);
//    TempData(const QString& room_name, const QString& room_introduce);
};

#endif // TEMPDATA_H
