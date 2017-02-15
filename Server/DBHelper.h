#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QMutex>

class DBHelper                          //创建一个对数据库的处理类  单例创建
{
public:
    static DBHelper* getInstance();

    bool createConnection();            //打开数据库
    void removeConnection();            //关闭数据库
private:
    static DBHelper* instance;
    DBHelper();
    static QMutex mutex;
    QSqlDatabase db;
};

#endif // DBHELPER_H
