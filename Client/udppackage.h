#ifndef UDPPACKAGE_H
#define UDPPACKAGE_H
#define MAXSIZE 1024

typedef struct imPack{
    char    data[MAXSIZE];        //图片中的数据
    int     width;              //图片的宽度
    int     height;             //图片的高度
    int     byteLine;           //图片每行的字节数
    int     byteTack;           //数据包中的有效数据大小
    int     maxnum;             //数据包数量
    bool    isLastPack;         //表示是否为最后一个包

}imPack_t;

typedef struct soundPack{
    char data[MAXSIZE];         //音频数据包
    int  dataLen;               //音频数据长度
}soundPack_t;

const unsigned int unitByte = MAXSIZE;

#endif // UDPPACKAGE_H
