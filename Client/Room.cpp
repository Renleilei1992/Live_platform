#include "Room.h"
#include "ui_Room.h"
#include "TempData.h"
#include <QDebug>
#include <QCamera>
#include <QCameraInfo>
#include "MyVideoSend.h"
#include <QVideoFrame>
#include <QImage>
#include <QPixmap>
#include "Danmu.h"
#include <QDesktopWidget>
#include <QRect>
#include <QTime>
#include <QUdpSocket>
#include "udppackage.h"
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioInput>
#include <QAudioOutput>
#include <QPoint>

Room::Room(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);
    qDebug()<<TempData::room_name<<" window 3";  //询问全局变量的问题，一打开程序这第三个窗口就打印了吗？(什么时候new room什么时候出)
    qDebug()<<TempData::room_introduce<<"window 3";
    ui->label_roomName->setText((TempData::room_name)+"的直播间");
    ui->label_introduce->setText(TempData::room_introduce);
    this->setWindowTitle((TempData::room_name)+"的直播间");//窗口名字

    //视频部分
    QCameraInfo info = QCameraInfo::defaultCamera();
    camera = new QCamera(info, this);

    MyVideoSend *myVideo = new MyVideoSend(this);
    camera->setViewfinder(myVideo);         //设置由 MyVideoSend 处理图像信息
    connect(myVideo, SIGNAL(videoChanged(const QVideoFrame&)),
            this, SLOT(videoChangedSlot(const QVideoFrame&)));
    //音频部分
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    //音频初始化
    QAudioDeviceInfo ininfo(QAudioDeviceInfo::defaultInputDevice());
    this->audioInput = new QAudioInput(ininfo,format);

    videoSocket = new QUdpSocket(this);
    soundSockt = new QUdpSocket(this);

}

void Room::videoChangedSlot(const QVideoFrame & myFrame)
{
    static int i = 0;
    i++;
//    qDebug()<<i;

    QDateTime time = QDateTime::currentDateTime();              //显示链接时间，方便日志管理
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ");
    QString time_str = " Time:" + str;

    QVideoFrame frame = myFrame;
    frame.map(QAbstractVideoBuffer::ReadOnly);  //将数据映射到物理内存中
    QImage image = QImage(frame.bits(),         //图片的字节数
                          frame.width(),        //图片的宽度
                          frame.height(),       //图片的高度
                          QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat())  //图片的格式
                          );

    QMatrix matrix;
    matrix.rotate(180);     //图片旋转180°

    image = image.transformed(matrix);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(ui->label_video->size());        //适应label尺寸
    ui->label_video->setPixmap(pixmap);                     //label显示图片

    image = image.scaled(30,30);

    int byteCount = image.byteCount();
    int width = image.width();
    int height = image.height();
    int byteLine = image.bytesPerLine();
//    qDebug()<<"图片大小: "<<byteCount;
//    qDebug()<<"图片宽度: "<<width;
//    qDebug()<<"图片高度: "<<height;
//    qDebug()<<"单行字节数:"<<byteLine;

    int byteWrite = 0;
    while(true)
    {
        imPack_t pack;
        memset(&pack, 0, sizeof(pack));
        pack.width = width;
        pack.height = height;
        pack.byteLine = byteLine;
        pack.maxnum = byteCount/unitByte;
        if(byteWrite < byteCount){
            //void *memcpy(void *dest, const void *src, size_t n);
            memcpy(pack.data, (char*)image.bits() + byteWrite,unitByte);
            byteWrite += unitByte;
//            qDebug()<<"IMAGE.BITS: "<<image.bits()<<"byteWrite: "<<byteWrite<<" "<<time_str;

            if(byteWrite >= byteCount){
                pack.byteTack = unitByte-(byteWrite - byteCount);
                pack.isLastPack = true;
            }else{
                pack.byteTack = unitByte;
                pack.isLastPack = false;
            }

            //数据写入到广播地址中
            videoSocket->writeDatagram((char*)&pack, sizeof(pack),
                                       QHostAddress(TempData::room_addr),9999);
        }else{
            break;
        }
    }
//    sleep_diy(100);//加在此处会引起直播间崩溃
}


//弹幕发送按钮槽函数(向服务器发送)
void Room::on_btn_send_clicked()
{
    QString msg_send = TempData::room_owner_name;
    msg_send += "(房主): ";
    msg_send += ui->line_sendMsg->text();
    emit send_barrage(msg_send,TempData::room_name);
}

//打开视频按钮槽函数
void Room::on_btn_openVideo_clicked()
{
    if(!TempData::check_video){
        qDebug()<<"广播地址: "<<TempData::room_addr;
        camera->start();
        ui->btn_openVideo->setText("关闭视频");
    }else{
        qDebug()<<"视频关闭成功！";
        ui->btn_openVideo->setText("开启视频");
        camera->stop();
    }
    TempData::check_video = !TempData::check_video;
}

//自定义延时函数
void Room::sleep_diy(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//警告！！！！processEvents会引起递归，造成栈溢出
    }
}

//在线用户名槽函数，根据服务器传回的数据对在线用户列表进行刷新处理
void Room::online_userName_slot(QString onlineUserName,int flagNum)
{
    if(flagNum == 1){
        ui->list_onlineUser->clear();//根据服务器传回的标志位信息确定是否需要刷新在线用户列表
        ui->list_onlineUser->addItem(onlineUserName);
    }else{
        ui->list_onlineUser->addItem(onlineUserName);
    }
}

//弹幕槽函数，根据服务器返回的弹幕数据进行操作
void Room::signal_barrage_backFromServer_slot(QString barrage)
{
    int temp = barrage.indexOf(",");
    if(temp > 0){
        ui->label_gift->setText("礼物:666");
    }

    ui->list_talking->addItem(barrage);
    QPoint point;
    point = ui->label_video->mapToGlobal(QPoint(0,0));
    qDebug()<<point;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QRect screenRect;
    screenRect = ui->label_video->rect();              //获取桌面大小的矩形

    danmu = new Danmu(this,barrage,"Red",1,screenRect,point);
}

//用户离开直播间槽函数，根据服务器返回的用户离开信息进行显示处理
void Room::quit_userName_slot(QString quitLiveUserName)
{
    QString leaveMsg = quitLiveUserName + "离开了直播间！";
    ui->list_talking->addItem(leaveMsg);
}

//离开直播间按钮槽函数（需要新增与线程通信的信号，通知线程关闭摄像头!!）
void Room::on_btn_quit_clicked()
{
    emit open_create_window();
    camera->stop();
    audioInput->stop();
    TempData::check_sound = false;
    TempData::check_video = false;
//    delete videoSocket;
//    delete soundSockt;
//    TempData::room_name = "0";
//    TempData::room_introduce = "0"; //静态全局变量需要恢复初始，不再记录上一个房间信息
    this->close();
}

//右上角关闭按钮事件处理，对其处理为 功能和离开直播间按钮一致
void Room::closeEvent(QCloseEvent *event)   //将窗口右上角的关闭按钮事件功能做成和quit按钮一致
{
    emit open_create_window();
    camera->stop();
    audioInput->stop();
    TempData::check_sound = false;
    TempData::check_video = false;
//    delete videoSocket;
//    delete soundSockt;
    this->close();
}

Room::~Room()
{
    delete ui;
}

//开启麦克风按钮槽函数
void Room::on_btn_openMike_clicked()
{
    if(!TempData::check_sound){
        ui->btn_openMike->setText("关闭麦克风");
        qDebug()<<"开启麦克风成功！ flag-1";
        audioInputIODevice = audioInput->start();   //开启麦克风
        qDebug()<<"开启麦克风成功！ flag-2";
        connect(audioInputIODevice, SIGNAL(readyRead()),
                this, SLOT(captureDataFromDevice()));
    }else{
        ui->btn_openMike->setText("开启麦克风");
        audioInput->stop();   //关闭麦克风
        qDebug()<<"关闭麦克风成功！";
    }
    TempData::check_sound = !TempData::check_sound;
}

//把获取的原始音频写入缓存，然后调用write函数把缓存里的数据写入输出设备即可听到声音
void Room::captureDataFromDevice()
{
    soundPack_t pack_send;
    memset(&pack_send,0,sizeof(pack_send));
    pack_send.dataLen = audioInputIODevice->read(pack_send.data,1024);
    soundSockt->writeDatagram((char*)&pack_send,sizeof(pack_send),
            QHostAddress(TempData::room_addr),10079);
}



