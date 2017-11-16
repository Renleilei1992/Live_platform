#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main44()
{
	int a ;
	int b; 
	char *    p ;
	//p = 0xaa11
	a = 10; //1 直接赋值  //cpu里面执行

	printf("&a: %d\n", &a);

	//2间接赋值 ==直接通过内存
	 *((int*)1245024) = 200;

	 printf("a: %d\n", a);

	 {
		p = 1245024;  // 间接赋值 通过指针

		*p = 300;
	 }

	 //3 对内存空间能不能在取 别名.....  C++ 引用 抛砖.....
	//1245024
	
	printf("hello...\n");
	system("pause");
	return ;
}

void sub1()
{

}