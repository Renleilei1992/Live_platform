#ifndef LIVEWATCH_H
#define LIVEWATCH_H

#include <QWidget>
#include <QString>
#include <QUdpSocket>

class Danmu;
class QAudioFormat;
class QIODevice;
class QAudioInput;
class QAudioOutput;

namespace Ui {
class LiveWatch;
}

class LiveWatch : public QWidget
{
    Q_OBJECT

public:
    explicit LiveWatch(QWidget *parent = 0);
    ~LiveWatch();
    QUdpSocket *videoRcvSocket;   //udp socket对象
    QUdpSocket *soundRcvSocket;   //音频接收套接字
public slots:
    void readyReadSlot();
    void readyReadSoundSlot();
    void online_userName_slot_live(QString onlineUserName,int flagNum); //接收到服务器发送的在线用户列表
    void signal_barrage_backFromServer_slot(QString barrage);//接收服务器的弹幕内容
    void quit_userName_slot(QString quitLiveUserName);      //接收来自服务器端某用户退出直播间信息

private slots:
    void on_btn_watch_clicked();

    void on_btn_quit_clicked();

    void on_btn_danmuSend_clicked();

    void on_btn_sound_clicked();

    void on_btn_gift_clicked();

signals:
    void quit_live();
    void send_barrage(QString msg,QString roomName);
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::LiveWatch *ui;
    Danmu *danmu;
    QIODevice *audioOutputIODevice;
    QAudioOutput *audioOutput;
};

#endif // LIVEWATCH_H
