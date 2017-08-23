#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//栈的开口向上向下,,测试 release和dubug;
//一般认为:栈开口向下 

//不管栈开口向上还是向下,buf的内存地址buf+1,永远向上的..


void main71()
{
	int a;
	int b ;

	char buf[128];  //静态联邦的时候 buf所代表的内存空间的标号 就已经定义下来了....

	printf("&a:%d , &b: %d \n", &a, &b);
	system("pause");
	return ;
}