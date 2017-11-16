

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//野指针产生的原因
//指针变量和它所指向的内存空间变量是两个不同的概念
// 释放了指针所致的内存空间  但是指针变量本身没有重置成null
//造成释放的时候 通过if (p1 != NULL)

//避免方法： 1）定义指针的时候 初始化成nuLL 2）释放指针所指向的内存空间后，把指针重置成NULL。
void main11()
{

	char  *p1 = NULL;
	p1 = (char *)malloc(100);
	if (p1 == NULL)
	{
		return ;
	}
	strcpy(p1, "11112222");

	printf("p1:%s \n", p1);

	if (p1 != NULL)
	{
		free(p1);
		p1 = NULL;
	}

	//

	if (p1 != NULL)
	{
		free(p1);
	}

	printf("hello...\n");
	system("pause");
	return ;
}
