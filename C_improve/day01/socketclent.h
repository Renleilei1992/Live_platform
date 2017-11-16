
// SOCKETCLIENT_H
#ifndef _SOCKETCLIENT_H
#endif  _SOCKETCLIENT_H

#ifdef  __cplusplus  
extern "C" {
#endif
//��һ��api����

//socket�ͻ��˻�����ʼ��
int socketclient_init(void **handle); //4

//socket�ͻ��˱��ķ���
int socketclient_send(void *handle, unsigned char *buf, int buflen); //2

//socket�ͻ��˱��Ľ���
int socketclient_recv(void *handle, unsigned char *buf, int *buflen); //2

//socket�ͻ��˻����ͷ�
int socketclient_destory(void *handle);


//�ڶ���api����

//socket�ͻ��˻�����ʼ��
int socketclient_init2(void **handle); //

//socket�ͻ��˱��ķ���
int socketclient_send2(void *handle, unsigned char *buf, int buflen);

//socket�ͻ��˱��Ľ���
int socketclient_recv2(void *handle, unsigned char **buf, int *buflen);
int socketclient_Free(unsigned char **buf);  //add

//socket�ͻ��˻����ͷ�
int socketclient_destory2(void **handle);

//���������
//1��ָ�� 
//2��ָ��
//void **handle���ͷ�װ�ĸ���  ҵ��ģ�͵ķ�װ�ĸ���

#ifdef  __cplusplus
}
#endif

#endif

