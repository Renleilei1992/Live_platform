#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

//1 �ṹ������һ���ṹ��
//2	 			�ṹ���ָ��
//3 �ṹ����һ�� �Լ����͵Ľṹ��Ԫ�ء�����err
//4 �ṹ���� ��һ�� ָ���Լ����͵�ָ��

//�������ͱ��ʣ��̶���С�ڴ��ı��� 

/*
typedef struct AdvTeacher 
{
	char name[64];
	int id;
	struct AdvTeacher AdvTeacher;
}AdvTeacher;  //���Լ����ʹ�С ��û��ȷ��������� �����Լ����͵�Ԫ�� �ǲ���ȷ��
//�ṹ�岻��Ƕ�׶��� ��ȷ�������������͵��ڴ��С�����䲻���ڴ棩
*/

typedef struct AdvTeacher2 
{
	char name[64];
	int id;
	struct AdvTeacher2 *p2;
}AdvTeacher;


//������Ƕ�׵���  �� �ṹ��������Ƕ�׶��� ��������ͬ�ĸ���
void main11()
{
	Teacher t1;
	//AdvTeacher  advT1; //
	printf("hello...\n");
	system("pause");
	main();
	return ;
}