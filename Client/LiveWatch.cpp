#include "LiveWatch.h"
#include "ui_LiveWatch.h"
#include <QHostAddress>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include "udppackage.h"
#include "TempData.h"
#include "Danmu.h"
#include <QDesktopWidget>
#include <QRect>
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioInput>
#include <QAudioOutput>

LiveWatch::LiveWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveWatch)
{
    ui->setupUi(this);

    ui->label_roomName->setText(TempData::room_name);
    ui->label_ownerName->setText("房主： " + TempData::room_ownerName);
    this->setWindowTitle((TempData::room_ownerName)+"的直播间");//窗口名字

    videoRcvSocket = new QUdpSocket(this);
    soundRcvSocket = new QUdpSocket(this);
    videoRcvSocket->bind(QHostAddress::AnyIPv4, 9999,
                       QUdpSocket::ShareAddress
                       |QUdpSocket::ReuseAddressHint);
    soundRcvSocket->bind(QHostAddress::AnyIPv4, 10079,
                       QUdpSocket::ShareAddress
                       |QUdpSocket::ReuseAddressHint);
    connect(videoRcvSocket,SIGNAL(readyRead()),
            this,SLOT(readyReadSlot()));
    connect(soundRcvSocket,SIGNAL(readyRead()),
            this,SLOT(readyReadSoundSlot()));

    //音频部分
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    //音频初始化
    QAudioDeviceInfo outinfo(QAudioDeviceInfo::defaultOutputDevice());
    this->audioOutput = new QAudioOutput(outinfo,format);
    audioOutputIODevice = this->audioOutput->start();   //音频播放
}

void LiveWatch::readyReadSlot()
{
    //QByteArray即可以处理二进制数据也可以处理文本数据
    static QByteArray *arry = new QByteArray(2800000, 0);
    //提供想arry中写入二进制数据的接口
    static QDataStream *stream = new QDataStream(arry,QIODevice::ReadWrite);
    static int i=0;
    while(videoRcvSocket->hasPendingDatagrams()){
        imPack_t pack;
        memset(&pack, 0, sizeof(pack));
        videoRcvSocket->readDatagram((char*)&pack, sizeof(pack));
        if(pack.isLastPack
//        ||i>=pack.maxnum
        ){
            stream->writeRawData(pack.data, pack.byteTack);
            //构建图片
            QImage im((uchar*)arry->data(),
                        pack.width,
                        pack.height,
                        pack.byteLine,
                        QImage::Format_RGB32);


            QPixmap pix = QPixmap::fromImage(im);
            pix = pix.scaled(ui->label_video->size());
            ui->label_video->setPixmap(pix);
            i=0;
            delete arry;
            delete stream;
            arry = new QByteArray(2800000, 0);
            stream = new QDataStream(arry, QIODevice::ReadWrite);

//            qDebug()<<"receiver true";
            //显示

        }else{
            //写入原始数据（二进制流）
            stream->writeRawData(pack.data, pack.byteTack);
//            qDebug()<<"receiver false";
        }
        ++i;
    }
}

void LiveWatch::readyReadSoundSlot()
{
    soundPack_t pack_rcv;
    memset(&pack_rcv,0,sizeof(pack_rcv));
    soundRcvSocket->readDatagram((char*)&pack_rcv,sizeof(pack_rcv));
    audioOutputIODevice->write(pack_rcv.data,pack_rcv.dataLen);
}

void LiveWatch::on_btn_watch_clicked()
{
    ui->label_roomName->setText(TempData::room_name);
    ui->label_video->setText(TempData::room_addr);
    videoRcvSocket->joinMulticastGroup(QHostAddress(TempData::room_addr));
}

void LiveWatch::on_btn_quit_clicked()
{
    videoRcvSocket->leaveMulticastGroup(QHostAddress(TempData::room_addr));
    emit quit_live();
    this->close();
}

LiveWatch::~LiveWatch()
{
    delete ui;
}

void LiveWatch::on_btn_danmuSend_clicked()
{
    QString msg_send = TempData::room_owner_name;
    msg_send += ": ";
    msg_send += ui->line_danmuSend->text();

    emit send_barrage(msg_send,TempData::room_name);
}

void LiveWatch::online_userName_slot_live(QString onlineUserName,int flagNum)
{
//    ui->list_onlineUserName->clear();
    if(flagNum == 1){
        ui->list_onlineUserName->clear();   //根据服务器传回的标志位信息确定是否需要刷新在线用户列表
        ui->list_onlineUserName->addItem(onlineUserName);
    }else{
        ui->list_onlineUserName->addItem(onlineUserName);
    }

}

void LiveWatch::signal_barrage_backFromServer_slot(QString barrage)
{
    int temp = barrage.indexOf(",");
    if(temp > 0){
        ui->label_gift->setText("礼物:666");
    }

    ui->list_danmu->addItem(barrage);
    QPoint point;
    point = ui->label_video->mapToGlobal(QPoint(0,0));
    qDebug()<<point;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QRect screenRect;
    screenRect = ui->label_video->rect();

    danmu = new Danmu(ui->label_video,barrage,"Green",1,screenRect,point);
}

void LiveWatch::quit_userName_slot(QString quitLiveUserName)
{
    QString leaveMsg = quitLiveUserName + "离开了直播间！";
    ui->list_danmu->addItem(leaveMsg);
}

void LiveWatch::on_btn_sound_clicked()
{
    if(!TempData::check_sound){
        ui->btn_sound->setText("关闭声音");
        qDebug()<<"开启声音成功！ flag-1";
        bool ret = soundRcvSocket->joinMulticastGroup(QHostAddress(TempData::room_addr));
        if(!ret){
            qDebug()<<"开启声音失败！ flag-2";
        }else{
            qDebug()<<"开启声音成功！ flag-2";
        }
    }else{
        ui->btn_sound->setText("开启声音");
        soundRcvSocket->leaveMulticastGroup(QHostAddress(TempData::room_addr));
        qDebug()<<"关闭声音成功！";
    }
    TempData::check_sound = !TempData::check_sound;
}

//右上角关闭按钮事件处理，对其处理为 功能和离开直播间按钮一致
void LiveWatch::closeEvent(QCloseEvent *event)   //将窗口右上角的关闭按钮事件功能做成和quit按钮一致
{
    TempData::check_sound = false;
    TempData::check_video = false;
    videoRcvSocket->leaveMulticastGroup(QHostAddress(TempData::room_addr));
    emit quit_live();
//    delete videoSocket;
//    delete soundSockt;
    this->close();
}


void LiveWatch::on_btn_gift_clicked()
{
    QString gift_send = TempData::room_owner_name;
    gift_send += ",打赏了666刀";

    emit send_barrage(gift_send,TempData::room_name);
}
