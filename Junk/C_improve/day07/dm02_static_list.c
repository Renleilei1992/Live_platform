#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//��
typedef struct Teacher
{
	int data;
	struct Teacher *next;
}Teacher;

//��̬����
	//�̶�����  �����ڴ���������

//��̬����


Teacher *CreatlIST()
{	
	Teacher t1, t2, t3;
	Teacher *p = NULL;
	t1.data = 1;
	t2.data = 2;
	t3.data = 3;

	t1.next = &t2;
	t2.next = &t3;
	t3.next = NULL;

	p  = &t1;
	while (p)
	{
		printf("data:%d ", p->data);
		p = p->next; //ָ������� 
	}
	return &t1;
}
void main21()
{
	Teacher * head = CreatlIST();
	printf("hello...\n");
	system("pause");
	return ;
}