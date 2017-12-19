#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTime>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include "socketThread.h"
#include "NetWorkManager.h"
#include <QMutex>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this,SLOT(timerUpdate()));
    timer->start(1000);

    server = new QTcpServer(this);  //创建服务器套接字管理对象
    qInstallMessageHandler(outputMessage);//进行日志处理(将所有 QDebug, QWarning, QCritical 内容都输出至日志地址)

    //关联客户端链接的套接字信号和槽, 当有客户端链接的时候，发出newConnection信号
    connect(server, SIGNAL(newConnection()),
            this, SLOT(new_connection_slot()));
}

void MainWindow::new_connection_slot()
{
    QTcpSocket *client_socket = server->nextPendingConnection();    //获取链接服务器的客户端套接字信息

    QHostAddress ip_client = client_socket->peerAddress();
    quint16 port_client = client_socket->peerPort();

    QDateTime time = QDateTime::currentDateTime();              //显示链接时间，方便日志管理
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ");
    QString time_str = " Time:" + str;

    QString info_client;
    info_client += "ip: " + ip_client.toString();
    info_client += ", port: " + QString::number(port_client);
    info_client += " connected!";
    info_client += time_str;

    qDebug()<<info_client;
    ui->textEdit->append(info_client);  //将链接到服务器的客户端IP等信息打印到服务器窗口中，方便记录日志

    SocketThread* socket_thread = new SocketThread(client_socket);
    connect(socket_thread, SIGNAL(signal_message(QTcpSocket*,const char*,qint64)),
            this, SLOT(signal_mes_slot(QTcpSocket*,const char*,qint64)));
    connect(socket_thread, SIGNAL(signal_room_info(QTcpSocket*,QString,QString)),
            this, SLOT(signal_room_info_slot(QTcpSocket*,QString,QString)));//接收直播间创建成功后的房间固有信息
    connect(socket_thread, SIGNAL(signal_quitRoom(QTcpSocket*,QString,QString)),
            this, SLOT(signal_quitRoom_slot(QTcpSocket*,QString,QString)));//接收关闭直播间后的处理函数
    connect(socket_thread, SIGNAL(signal_enterLiveRoom(QTcpSocket*,QString,QString)),
            this, SLOT(signal_enterLiveRoom_slot(QTcpSocket*,QString,QString)));//接收进入直播间观看的处理函数
    connect(socket_thread, SIGNAL(signal_quitLiveRoom(QTcpSocket*,QString,QString)),
            this, SLOT(signal_quitLiveRoom_slot(QTcpSocket*,QString,QString)));//接收离开直播间观看的处理函数
    connect(socket_thread, SIGNAL(signal_refresh_onlineUser(QTcpSocket*,QString)),
            this, SLOT(signal_refresh_onlineUser_slot(QTcpSocket*,QString)));//接收刷新在线用户列表的处理函数
    connect(socket_thread, SIGNAL(signal_barrage(QString,QString)),
            this, SLOT(signal_barrage_slot(QString,QString)));               //接收到弹幕信息并加以处理

    QThread *thread_client = new QThread(this);     //创建客户线程用于处理客户发送的数据包套接字(拆包)
    socket_thread->moveToThread(thread_client);     //将接收到的套接字事件转移到客户线程中处理
    thread_client->start();                         //线程启动

    connect(thread_client, SIGNAL(finished()),
            socket_thread, SLOT(deleteLater()));    //线程结束，销毁socket_thread对象
    connect(thread_client, SIGNAL(finished()),
            thread_client, SLOT(quit()));           //线程结束，线程自动退出

    //将客户端所有的处理对象放入容器中
    NetWorkManager* instance = NetWorkManager::getInstance();
    instance->insert_user(socket_thread);

}

void MainWindow::on_btn_listen_clicked()
{
    if(!server->isListening()){
        //启动服务器监听（端口号不能和正在运行的进程相同）
        if(!server->listen(QHostAddress::Any, 8888)){
            ui->textEdit->append("listen failed!");
            ui->btn_listen->setEnabled(true);
            ui->btn_stop->setEnabled(false);
            return;
        }else{
            QDateTime time = QDateTime::currentDateTime();
            QString str = time.toString("yyyy-MM-dd hh:mm:ss ");
            QString show_str = "Server start ,listen successful!  Time:" + str;
            ui->textEdit->append(show_str);
            ui->btn_listen->setEnabled(false);
            ui->btn_stop->setEnabled(true);
            return;
        }
    }
    ui->textEdit->append("already listen!");
}

//统一的信息反馈槽函数，响应很多信号
void MainWindow::signal_mes_slot(QTcpSocket* socket,const char *data,qint64 len)
{
//    qDebug()<<"no return to client! careful!!";
    socket->write(data,len);                        //将信息写入套接字发送回客户端
}

//房主建立直播间槽函数（向容器中加入房间基本信息键值对）
void MainWindow::signal_room_info_slot(QTcpSocket* socket, QString roomName, QString roomOwnerName)
{
    QMap<QString,QTcpSocket*> userInRoom_map;
    userInRoom_map.insert(roomOwnerName,socket);
    room_online_map.insert(roomName,userInRoom_map);//双重嵌套容器，用以保存直播间信息
}

//房主关闭直播间槽函数（删除容器中的房间信息键值对）
void MainWindow::signal_quitRoom_slot(QTcpSocket* socket, QString roomName, QString userName)
{
    QMap<QString,QMap<QString,QTcpSocket*> >::iterator iter_room = room_online_map.find(roomName);
    room_online_map.erase(iter_room);//利用键值删除map容器内的条目（直播间关闭）
}

//观众进入直播间槽函数
void MainWindow::signal_enterLiveRoom_slot(QTcpSocket* socket, QString roomName, QString userName)
{
    QMap<QString,QMap<QString,QTcpSocket*> >::iterator iter_room = room_online_map.find(roomName);
//    QMap<QString,QTcpSocket*> userInRoom_map;//不能采用中间变量接收，方法有误!!警醒自己
    if(iter_room != room_online_map.end()){
//        userInRoom_map = iter_room.value();//根据进入的直播间名字查询到的容器，使用 userInRoom_map接收
//        userInRoom_map.insert(userName,socket);//观众进入直播间，由于直播间已经打开，插入寻找到的直播间用户容器
        iter_room.value().insert(userName,socket);//观众进入直播间，由于直播间已经打开，插入寻找到的直播间用户容器
        qDebug()<<"find room_online success! userENTER: "<<userName<<" room: "<<roomName;

        //此处存在漏洞，若大量用户相同或者相近时间段内同时登陆，服务器主线程任务将会来不及分配
        QMap<QString,QTcpSocket*>::iterator iter_userSocket;//准备遍历在线用户容器,迭代器取出socket
        QMap<QString,QTcpSocket*>::iterator iter_userName;//准备遍历在线用户容器,迭代器取出name
        static int count = 1;
        string find_userName;
        QTcpSocket* find_userSocket;
        Protocol package_sendBack;
        //此二层嵌套循环极大地加重了服务器负担，可考虑优化或者重构
        for(iter_userSocket = iter_room.value().begin(); iter_userSocket != iter_room.value().end(); ++iter_userSocket)
        {//第一层循环用来取出每一个键值对的socket
            find_userSocket = iter_userSocket.value();//接收迭代器从容器中取出的socket
            for(iter_userName = iter_room.value().begin(); iter_userName != iter_room.value().end(); ++iter_userName)
            {//第二层循环，迭代器每次取出一个在线用户名即向当前所在socket写入该在线用户
                memset(&package_sendBack,0,sizeof(Protocol));
                package_sendBack.type = REFRESH_BACK;
                if(count == 1){
                    package_sendBack.flag = 1;//标志位的目的是为了客户端判断是否为第一个包，如果是，就需要清除一下list的旧信息
                }else{
                    package_sendBack.flag = 0;
                }
                count++;
                qDebug()<<"online userName: "<<iter_userName.key();
                find_userName = iter_userName.key().toStdString();
                find_userName.copy(package_sendBack.userName,find_userName.size(),0);
                find_userSocket->write((const char*)&package_sendBack, sizeof(package_sendBack));
            }
            qDebug()<<"online user number: "<<sqrt(count)<<"   refresh success!";
            count = 1;		//还原count初值
        }

    }else{
        qDebug()<<"find room_online failed!";
    }
}

//观众离开直播间槽函数（容器操作）(对待离开直播间用户的socket，已无需对其进行写入信息）
void MainWindow::signal_quitLiveRoom_slot(QTcpSocket* socket, QString roomName, QString userName)
{
    QMap<QString,QMap<QString,QTcpSocket*> >::iterator iter_room = room_online_map.find(roomName);
    if(iter_room != room_online_map.end()){
        //根据退出直播间的用户名在直播间容器中寻找该键
        QMap<QString,QTcpSocket*>::iterator iter_userNameQuit = iter_room.value().find(userName);
        if(iter_userNameQuit != iter_room.value().end()){
            iter_room.value().erase(iter_userNameQuit); //再根据寻找到的迭代器将该用户键值从map中删除
            qDebug()<<"quit room success! userQUIT: "<<userName<<" room: "<<roomName;

            string quit_userName = userName.toStdString();
            //遍历直播间内在线用户信息并向每个socket发送某用户离开的信息（只是单纯地发送回客户端一个离开直播间的观众名字），第一步！
            QMap<QString,QTcpSocket*>::iterator iter_userSocket;//准备遍历在线用户容器,迭代器取出socket
            static int count = 0;
            QTcpSocket* find_userSocket;
            Protocol package_sendBack;
            for(iter_userSocket = iter_room.value().begin(); iter_userSocket != iter_room.value().end(); ++iter_userSocket)
            {//第一层循环用来取出每一个键值对的socket
                count++;
                find_userSocket = iter_userSocket.value();//接收迭代器从容器中取出的socket
                memset(&package_sendBack,0,sizeof(Protocol));
                package_sendBack.type = QUIT_BACK;
                qDebug()<<"OL - User - name: "<<iter_userSocket.key();
                quit_userName.copy(package_sendBack.userName,quit_userName.size(),0);
                find_userSocket->write((const char*)&package_sendBack, sizeof(package_sendBack));
            }
            qDebug()<<"发送到的用户数: "<<count<<" QUIT_BACK success!";
            count = 0;

            //某观众离开之后，再次执行双重for循环对该房间每个在线用户再次刷新一次在线用户列表，第二步！
            QMap<QString,QTcpSocket*>::iterator iter_userName;//准备遍历在线用户容器,迭代器取出name
            static int count1 = 1;
            string find_userName;
            //此二层嵌套循环极大地加重了服务器负担，可考虑优化或者重构
            for(iter_userSocket = iter_room.value().begin(); iter_userSocket != iter_room.value().end(); ++iter_userSocket)
            {//第一层循环用来取出每一个键值对的socket
                find_userSocket = iter_userSocket.value();//接收迭代器从容器中取出的socket
                for(iter_userName = iter_room.value().begin(); iter_userName != iter_room.value().end(); ++iter_userName)
                {//第二层循环，迭代器每次取出一个在线用户名即向当前所在socket写入该在线用户
                    memset(&package_sendBack,0,sizeof(Protocol));
                    package_sendBack.type = REFRESH_BACK;
                    if(count1 == 1){
                        package_sendBack.flag = 1;
                    }else{
                        package_sendBack.flag = 0;
                    }
                    count1++;
                    qDebug()<<"(STEP2) - online userName: "<<iter_userName.key();
                    find_userName = iter_userName.key().toStdString();
                    find_userName.copy(package_sendBack.userName,find_userName.size(),0);
                    find_userSocket->write((const char*)&package_sendBack, sizeof(package_sendBack));
                }
                count1 = 1;
            }
        }else{
            qDebug()<<"QUIT userName find failed!";
        }
    }else{
        qDebug()<<"find room_online failed!";
    }
}

//在线用户列表刷新槽函数，用以刷新在线用户列表并向每个在线用户发送在线用户的信息
void MainWindow::signal_refresh_onlineUser_slot(QTcpSocket* socket, QString roomName)
{
    QMap<QString,QMap<QString,QTcpSocket*> >::iterator iter_room = room_online_map.find(roomName);
    if(iter_room != room_online_map.end()){
        qDebug()<<"find room_online success!";

        QMap<QString,QTcpSocket*>::iterator iter_user;//准备遍历在线用户容器
        static int count = 1;
        string find_userName;
        Protocol package_sendBack;
        memset(&package_sendBack,0,sizeof(Protocol));
        package_sendBack.type = REFRESH_BACK;
        //此处逻辑需要重构，暂时先做试验（此处只能对房主刷新一次）
        for(iter_user = iter_room.value().begin(); iter_user != iter_room.value().end(); ++iter_user)
        {
            if(count == 1){//标志位是1，证明是刷新用户列表的第一个数据包，此时需要清空旧的在线用户列表
                package_sendBack.flag = 1;
            }else{
                package_sendBack.flag = 0;
            }
            count++;
            find_userName = iter_user.key().toStdString();
            find_userName.copy(package_sendBack.userName,find_userName.size(),0);
            qDebug()<<"online userName: "<<iter_user.key();
            socket->write((const char*)&package_sendBack, sizeof(package_sendBack));//value先搁置
        }
        qDebug()<<"online user number: "<<count<<"   refresh success!";
        count = 1;
    }else{
        qDebug()<<"find room_online failed!";
    }
}

//发送弹幕槽函数，（如果房间关闭了，那么不能向其余用户发送，会导致服务器崩溃）
void MainWindow::signal_barrage_slot(QString room_name, QString barrageContent)
{
    QMap<QString,QMap<QString,QTcpSocket*> >::iterator iter_room = room_online_map.find(room_name);
    if(iter_room != room_online_map.end()){
        qDebug()<<"find room_online success!"<<" DANMU-room: "<<room_name;

        //遍历直播间内在线用户信息并向每个socket发送弹幕内容（只有当房间存在的时候才能发送）
        QMap<QString,QTcpSocket*>::iterator iter_userSocket;//准备遍历在线用户容器,迭代器取出socket
        static int count = 0;
        string barrageSendBack;
        QTcpSocket* find_userSocket;
        Protocol package_sendBack;
        //此二层嵌套循环极大地加重了服务器负担，可考虑优化或者重构
        for(iter_userSocket = iter_room.value().begin(); iter_userSocket != iter_room.value().end(); ++iter_userSocket)
        {//第一层循环用来取出每一个键值对的socket
            count++;
            find_userSocket = iter_userSocket.value();//接收迭代器从容器中取出的socket
            memset(&package_sendBack,0,sizeof(Protocol));
            package_sendBack.type = DANMU_BACK;
            qDebug()<<"DANUMU - room: "<<iter_userSocket.key();
            barrageSendBack = barrageContent.toStdString();
            barrageSendBack.copy(package_sendBack.barrage,barrageSendBack.size(),0);
            find_userSocket->write((const char*)&package_sendBack, sizeof(package_sendBack));
        }
        qDebug()<<"弹幕发送到的用户数: "<<count<<" DANMU_BACK success!";
        count = 0;

    }else{
        qDebug()<<"find room_online failed!";
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
//    qDebug()<<str;//打印出当前时间
    ui->label_showTime->setText(str);
}

void MainWindow::on_btn_stop_clicked()
{
    ui->btn_listen->setEnabled(true);   //将启动监听的按钮设置为可以使用
    server->close();                    //关闭服务器监听端口

    QDateTime time = QDateTime::currentDateTime();          //显示关闭服务器时间，方便日志查询
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ");
    QString show_str = "Server shutDown!                  Time:" + str;
    ui->textEdit->append(show_str);
    ui->btn_stop->setEnabled(false);
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file("D://Working//Qt_Demo//Server//log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
//    qDebug()<<"open success!";
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}
