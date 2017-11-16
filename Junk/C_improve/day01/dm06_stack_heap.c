

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//堆
char *getMem(int num)
{
	char *p1 = NULL;
	p1 = (char *)malloc(sizeof(char) * num);
	if (p1 == NULL)
	{
		return NULL;
	}
	return p1;
}

//栈
//注意 return不是把内存块 64个字节,给return出来,而是把内存块的首地址(内存的标号0xaa11) ,返回给 tmp

// 理解指针的关键,是内存. 没有内存哪里的指针 

//
char *getMem2()
{
	char buf[64]; //临时变量 栈区存放
	strcpy(buf, "123456789");
	//printf("buf:%s\n", buf);
	return buf;
}

void main61()
{
	char *tmp = NULL;
	tmp = getMem(10);
	if (tmp == NULL)
	{
		return ;
	}
	strcpy(tmp, "111222"); //向tmp做指向的内存空间中copy数据

	//tmp = getMem2();
	tmp = 0xaa11;

	printf("hello..tmp:%s.\n", tmp);
	system("pause");
	return ;
}