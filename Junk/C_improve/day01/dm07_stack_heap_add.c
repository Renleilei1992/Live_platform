#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//ջ�Ŀ�����������,,���� release��dubug;
//һ����Ϊ:ջ�������� 

//����ջ�������ϻ�������,buf���ڴ��ַbuf+1,��Զ���ϵ�..


void main71()
{
	int a;
	int b ;

	char buf[128];  //��̬�����ʱ�� buf��������ڴ�ռ�ı�� ���Ѿ�����������....

	printf("&a:%d , &b: %d \n", &a, &b);
	system("pause");
	return ;
}