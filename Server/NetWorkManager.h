#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QMutex>
#include <vector>
using namespace std;
class SocketThread;

class NetWorkManager
{
public:
    static NetWorkManager* getInstance();
    void insert_user(SocketThread*);
    vector<SocketThread*> get_all_clients()const;

private:
    static NetWorkManager* instance;
    NetWorkManager();
    static QMutex mutex;
    vector<SocketThread* > clients;
};

#endif // NETWORKMANAGER_H
