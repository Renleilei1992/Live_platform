#include "NetWorkManager.h"
#include "socketThread.h"

NetWorkManager* NetWorkManager::instance = 0;
QMutex NetWorkManager::mutex;
NetWorkManager::NetWorkManager()
{

}


NetWorkManager* NetWorkManager::getInstance()
{
    if(nullptr == instance){
        mutex.lock();
        if(nullptr == instance){
            instance = new NetWorkManager();
        }
        mutex.unlock();
    }
    return instance;
}

void NetWorkManager::insert_user(SocketThread *sh)
{
    clients.push_back(sh);
}

vector<SocketThread* > NetWorkManager::get_all_clients()const
{
    return clients;
}
