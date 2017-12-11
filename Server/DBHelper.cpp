#include "DBHelper.h"
#include <QSqlError>
#include <QDebug>

DBHelper* DBHelper::instance = 0;
QMutex DBHelper::mutex;                             //加锁

DBHelper::DBHelper()
{
    db = QSqlDatabase::addDatabase("QSQLITE");      //加载数据库驱动
}

DBHelper* DBHelper::getInstance()
{
    if(nullptr == instance){
        mutex.lock();
        if(nullptr == instance){
            instance  = new DBHelper();
        }
        mutex.unlock();
    }
    return instance;
}

// 此处加载的是 sqlite3数据库 是否可以添加其他数据库?!
bool DBHelper::createConnection()
{
    db.setDatabaseName("D://Working//Qt_Demo//Server//user.db");          //打开user.db数据库
    if(!db.open()){
        qDebug()<<db.lastError().text()<<"flag 2";
        return false;
    }else{
        qDebug()<<"open success!"<<"flag 2";
    }
    return true;
}

void DBHelper::removeConnection()
{
    db.close();
    db.removeDatabase("D://Working//Qt_Demo//Server//user.db");           //关闭数据库
}
