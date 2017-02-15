#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include "protocol.h"
#include <QObject>
#include <QApplication>
#include <QTime>

class QTcpSocket;

class SocketThread : public QObject
{
    Q_OBJECT
public:
    QTcpSocket* getSocket()const { return socket; }     //获取客户端socket
    explicit SocketThread(QTcpSocket *socket,
                          QObject *parent = 0);

    void sleep_diy(unsigned int msec);                      //自己新建的延时函数
    void register_user(Protocol* package_user_register);    //注册处理
    void login_user(Protocol* package_user_login);          //登录处理
    void create_room(Protocol* package_user_create);        //创建房间处理
    void check_online_room(Protocol* package_user_check);   //查询在线房间
    void quit_room(Protocol* package_user_quit);            //退出房间
    void offline_handle(Protocol* package_user_offline);    //用户下线

private:
    QTcpSocket* socket;

signals:
    void signal_message(QTcpSocket* , const char* , qint64);
    void signal_refuse_register(QTcpSocket* , const char* , qint64);
    void signal_room_info(QTcpSocket* ,QString ,QString );  //直播间一创建成功即刻向主线程发送房间信息（主线程使用容器将信息保存）
    void signal_quitRoom(QTcpSocket* ,QString ,QString );   //关闭直播间即刻向主线程发送房间信息
    void signal_enterLiveRoom(QTcpSocket* ,QString ,QString );//用户进入某直播间即刻向主线程发送房间信息
    void signal_quitLiveRoom(QTcpSocket* ,QString ,QString );//用户退出某直播间即刻向主线程发送房间信息
    void signal_refresh_onlineUser(QTcpSocket* ,QString);   //刷新直播间在线用户列表信号，主线程接收并处理
    void signal_barrage(QString, QString);                  //直播间弹幕信息信号，主线程接收并发送到各个客户端

public slots:
    void ready_read_slot();
};

#endif // SOCKETTHREAD_H
