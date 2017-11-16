#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void main2()
{
	int i = 0;

	//指针数组
	char *   p1[] = {"123", "456", "789"};


	//二维数组
	char p2[3][4]  = {"123", "456", "789"};

	//手工二维内存
	char **p3 = (char **)malloc(3 * sizeof(char *)); //int array[3];

	for (i=0; i<3; i++)
	{
		p3[i] = (char *)malloc(10*sizeof(char)); //char buf[10]

		sprintf(p3[i], "%d%d%d", i, i, i);
	}
}


void main555()
{
	printf("hello...\n");
	system("pause");
	return ;
}