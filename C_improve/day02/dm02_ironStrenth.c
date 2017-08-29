#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main01()
{

	char *p1 = NULL;

	strcpy(p1, "abcdefg");
	printf("hello...\n");
	system("pause");
	return ;
}

void main02()
{

	char *p1 = NULL;
	p1 = 0x00077;

	strcpy(p1, "abcdefg");
	printf("hello...\n");
	system("pause");
	return ;
}

void main22()
{
	char	buf[128]; //c可以在栈上分配内存
	int		i; 
	int     j = 0;

	char	*p2 = NULL; //c可以在栈上分配内存

	char *p1 = NULL;

	p1 = &buf[0]; //不断的修改p1的值 相当于 不断改变指针的指向
	p1 = &buf[1];
	p1 = &buf[2];

	for (i=0; i<10; i++)
	{
		p1 = buf[i];
	}

	p2 = (char *)malloc(100);
	strcpy(p2, "abcdefg1212333333333311");

	for (i=0; i<10; i++)
	{
		p1 = p2+i;
		printf("%c ", *p1);
	}

	printf("hello...\n");
	system("pause");
	return ;
}


