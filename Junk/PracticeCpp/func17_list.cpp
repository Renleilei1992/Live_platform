#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

/*
struct Teacher 
{
	char name[64];
	int id;
	char *p;
	char **p2;
};
typedef struct Teacher Teacher ;
*/


typedef struct Student 
{
	char name[64];
	int id;

}Student;

typedef struct Teacher 
{
	char name[64];
	int id;
	char *p;
	char **p2;
	Student s1;
	Student *p3;
}Teacher;

//1 结构体中套一个结构体
//2	 			结构体的指针
//3 结构中套一个 自己类型的结构体元素。。。err
//4 结构体中 套一个 指向自己类型的指针

//数据类型本质：固定大小内存块的别名 

/*
typedef struct AdvTeacher 
{
	char name[64];
	int id;
	struct AdvTeacher AdvTeacher;
}AdvTeacher;  //在自己类型大小 还没有确定的情况下 引用自己类型的元素 是不正确的
//结构体不能嵌套定义 （确定不了数据类型的内存大小，分配不了内存）
*/

typedef struct AdvTeacher2 
{
	char name[64];
	int id;
	struct AdvTeacher2 *p2;
}AdvTeacher;


//函数的嵌套调用  和 结构数据类型嵌套定义 是两个不同的概念
void main11()
{
	Teacher t1;
	//AdvTeacher  advT1; //
	printf("hello...\n");
	system("pause");
	main();
	return ;
}
