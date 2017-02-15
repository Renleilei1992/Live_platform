#ifndef ROOM_H
#define ROOM_H

#include <QWidget>
#include <QString>
#include <QApplication>
#include <QTime>
#include <QCloseEvent>

class Danmu;
class QUdpSocket;
class QCamera;
class QVideoFrame;
class QAudioFormat;
class QIODevice;
class QAudioInput;
class QAudioOutput;

namespace Ui {
class Room;
}

class Room : public QWidget
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = 0);
    ~Room();
protected:
    void closeEvent(QCloseEvent *event);

public:
    void sleep_diy(unsigned int msec);                      //自己新建的延时函数

private slots:

    void videoChangedSlot(const QVideoFrame&);

    void on_btn_send_clicked();

    void on_btn_quit_clicked();

    void online_userName_slot(QString onlineUserName,int flagNum);       //在线用户列表刷新

    void signal_barrage_backFromServer_slot(QString barrage);//接收到来自服务器返回的弹幕内容

    void quit_userName_slot(QString quitLiveUserName);      //接收来自服务器端某用户退出直播间信息

    void captureDataFromDevice();   //音频槽函数

    void on_btn_openVideo_clicked();

    void on_btn_openMike_clicked();

private:
    Ui::Room *ui;
    Danmu *danmu;
    QCamera *camera;
    QIODevice *audioInputIODevice;
//    QIODevice *audioOutputIODevice;
    QAudioInput *audioInput;
//    QAudioOutput *audioOutput;
    QUdpSocket *videoSocket;        //视频流占用套接字
    QUdpSocket *soundSockt;         //音频流占用套接字

signals:
    void open_create_window();
    void send_barrage(QString msg,QString roomName);

    void shutDown();    //对线程发送关闭信号
    void openUp();      //对线程发送开启摄像头信号

};

#endif // ROOM_H
