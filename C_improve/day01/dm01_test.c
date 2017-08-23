
#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//socket客户端环境初始化
int socketclient_init2(void **handle)
{
	return 0;
}

//socket客户端报文发送
int socketclient_send2(void *handle, unsigned char *buf, int buflen)

{
	return 0;
}

//socket客户端报文接受
int socketclient_recv2(void *handle, unsigned char **buf, int *buflen)

{
	return 0;
}

//socket客户端环境释放
int socketclient_destory2(void **handle)

{
	return 0;
}

void main()
{
	printf("hello...\n");
	system("pause");
	return ;
}
