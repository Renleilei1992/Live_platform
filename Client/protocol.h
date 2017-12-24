#ifndef PROTOCOL_H
#define PROTOCOL_H
#define SIZE 40
#define MES_MAX 512

enum dataType{
    REG_INFO,			//
    REG_FAIL,
    REG_SUCCESSFUL,

    LOG_INFO,			// 登录信息
    LOG_FAIL,
    LOG_SUCCESSFUL,

    CREATE_INFO,		//创建信息
    CREATE_FAIL,
    CREATE_SUCCESSFUL,

    CHECK_INFO,			//核对信息
    CHECK_BACK,

    QUIT_ROOM,			//离开直播间
    ENTER_LIVE,			//加入直播间
    QUIT_LIVE,			//退出直播
    QUIT_BACK,			//

    DANMU_INFO,			//弹幕信息
    DANMU_BACK,

    REFRESH_INFO,
    REFRESH_BACK,

    OFFLINE_INFO
};

typedef struct protocol{
    dataType type;                    //数据包类型
    char userName[SIZE];              //用户名
    char userPwd[SIZE];               //用户密码
    char roomName[SIZE];              //直播间名
    char roomAddr[SIZE];              //直播间地址
    int gift;                         //礼物金额(根据金额判断礼物种类)
    int followNum;                    //关注数量
    char targetName[SIZE];            //弹幕发送对象及私信对象
    char barrage[SIZE];               //弹幕内容(或者私信内容)
    int flag;                         //标志位

}Protocol;

#endif // PROTOCOL_H
