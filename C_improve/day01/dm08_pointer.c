#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main81()
{
	int a = 10;
	char *p1 = 100;  //分配4个字节的内存
	char ****p2 = 100;


	int *p3 = NULL;

	p3 = &a;

	*p3 = 20; //间接的修改a的值
	//*就像一把钥匙 通过一个地址(&a),去修改a变量的标示的内存空间

	{
		int c = 0;
		c = *p3;  //c=20
		//*p放在=号左边 写内存
		//*p放=号的右边 读内存
		printf("c:%d \n", c);
	}

	{
		char *p4 = NULL;
		p4 = (char *)malloc(100);
		p4 = (char *)malloc(200); //0xcc11

	}

	printf("a:%d , p1:%d , p2: %d", sizeof(a), sizeof(p1), sizeof(p2));
	printf("hello...\n");

	
	system("pause");
	return ;
}

char *getStr81()
{
	char *tmp = NULL;
	tmp = "abcdefgf";
	return tmp;
}

/*
int getABC1(char    *p1);  int getABC1(char*       p1);
int	getABC2(char **    p2);	int	getABC2(char *    *p2);   int	getABC2(char           **p2);
int	getABC3(char ***p3);
int	getABC4(char (*p4)[30]);  int	getABC4(char (*p4)            [30]);
int	getABC5(char p5[10][30]); int	getABC5(char p5[10][30]);

//指针做函数参数 形参有多级指针的时候, 
//站在编译器的角度 ,只需要分配4个字节的内存(32bit平台)
//当我们使用内存的时候,我们才关心指针所指向的内存 是一维的还是二维的


*/


void main()
{
	char *p = getStr81();
	printf("p:%s \n", p);
	*(p+2) = 'r';  //经常出现的错误 保证指针所指向的内存空间 可以被修改
	system("pause");
	return ;
}