#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// 数据类型的用途
//数据类型的本质:固定大小内存块的别名
// b &b 数组数据类型 (定义一个1 数组类型 2数组指针  3 数组类型和数组指针类型的关系) ====>压死初学者的三座大山  抛砖
//

void main31()
{
	int a; //告诉c编译器分配4个字节的内存
	int b[10] ; //告诉c编译器分配40个自己内存

	printf("b:%d, b+1:%d, &b:%d, &b+1:%d \n", b, b+1, &b, &b+1);

	printf("sizeof(b):%d \n", sizeof(b));  //40
	printf("sizeof(a):%d \n ", sizeof(a)); //4
	 
	// b+1  &b+1 结果不一样  //b &b所代表的数据类型不一样
	//b 代表的数组首元素的地址
	//&b代表的是整个数组的地址  

	//
	printf("hello....\n");
	system("pause");
}

struct Teacher
{
	char name[64];
	int age;
}Teacher;


typedef struct Teacher2
{
	char name[64];
	int age;
}Teacher2;
//数据别名 typedef

typedef int u32;

void main33()
{
	int a; //告诉c编译器分配4个字节的内存
	int b[10] ; //告诉c编译器分配40个自己内存

	struct Teacher t1;

	Teacher2 t2;
	t1.age = 31;

	printf("u32:%d \n", sizeof(u32));

	{
		char *p2 = NULL;
		void *p1 = NULL;
		p2 = (char *)malloc(100);

		p1 = &p2;
	}
	{
		//void a;//编译器不知道如何分配内存
	}

	printf("hello....\n");
	system("pause");
}