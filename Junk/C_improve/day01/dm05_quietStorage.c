#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * getStr1()
{
	char *p1 = "abcdefg2";
	return p1;
}
char *getStr2()
{
	char *p2 = "abcdefg2";
	return p2;
}

void main55()
{
	char *p1 = NULL;
	char *p2 = NULL;
	p1 = getStr1();
	p2 = getStr2();

	//��ӡp1 p2 ��ָ���ڴ�ռ������
	printf("p1:%s , p2:%s \n", p1, p2);

	//��ӡp1 p2 ��ֵ
	printf("p1:%d , p2:%d \n", p1, p2);

	printf("hello...\n");
	system("pause");
	return ;
}