#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// �������͵���;
//�������͵ı���:�̶���С�ڴ��ı���
// b &b ������������ (����һ��1 �������� 2����ָ��  3 �������ͺ�����ָ�����͵Ĺ�ϵ) ====>ѹ����ѧ�ߵ�������ɽ  ��ש
//

void main31()
{
	int a; //����c����������4���ֽڵ��ڴ�
	int b[10] ; //����c����������40���Լ��ڴ�

	printf("b:%d, b+1:%d, &b:%d, &b+1:%d \n", b, b+1, &b, &b+1);

	printf("sizeof(b):%d \n", sizeof(b));  //40
	printf("sizeof(a):%d \n ", sizeof(a)); //4
	 
	// b+1  &b+1 �����һ��  //b &b��������������Ͳ�һ��
	//b �����������Ԫ�صĵ�ַ
	//&b���������������ĵ�ַ  

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
//���ݱ��� typedef

typedef int u32;

void main33()
{
	int a; //����c����������4���ֽڵ��ڴ�
	int b[10] ; //����c����������40���Լ��ڴ�

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
		//void a;//��������֪����η����ڴ�
	}

	printf("hello....\n");
	system("pause");
}