#include "stdlib.h"
#include "string.h"
#include "stdio.h"
//����
void main()
{
	int	i = 0,j = 0;
	int	tmp = 0;
	int a[] = {6,5,4,7,3,1,2};
	printf("����֮ǰ\n");
	for (i=0; i<7; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");	
	//����
	//���ѭ��	��i=0��ʱ��, ��j��1===N���б仯
	//���ѭ��	��i=1��ʱ��, ��j��2===N���б仯
	//			��i=2��ʱ��, ��j��3===N���б仯
	//����: ����һ������i����,������һ������j���б仯;��һ�� ���ν���
	for(i=0; i<7; i++)  
	{
		for (j=i+1; j<7; j++)  //�ڲ�ѭ��: a[i] �� a[j]�Ƚ�
		{
			if (a[i] > a[j])
			{
				tmp = a[i];
				a[i]= a[j];
				a[j] = tmp;
				for(int k=0; k<7; k++){
					printf("%d ",a[k]);
				}
				printf("\n");
			}
		}
	}
	printf("����֮��\n");
	for (i=0; i<7; i++)
	{
		printf("%d ", a[i]);
	}
	printf("hello...\n");
	system("pause");
}

//void printArray(int a[7], int num)
//void printArray(int a[], int num)
void printArray(int *a, int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		printf("%d ", a[i]);
	}
}
void sortArray(int a[7], int num)
//void sortArray(int a[], int num)
//void sortArray(int *a, int num)
{
	int i , j , tmp ;
	int		num2 = 0;

	num2 = sizeof(a)/sizeof(a[0]);
	printf("num:%d \n", num2);
	//ʵ�ε�a �� �βε�a ���������ͱ��ʲ�һ��
	//�β��е����� ,���������������ָ�봦�� ����C���Ե���ɫ
	for(i=0; i<num; i++) 
	{
		for (j=i+1; j<num; j++)  //�ڲ�ѭ��: a[i] �� a[j]�Ƚ�
		{
			if (a[i] > a[j])
			{
				tmp = a[i];
				a[i]= a[j];
				a[j] = tmp;
			}
		}
	}
}
//�����������������˻�����  �˻�Ϊһ��ָ��, 
//1 ��ȷ��������������ڴ��׵�ַ���������Ч���ȴ��������ú���
//2 //ʵ�ε�a �� �βε�a ���������ͱ��ʲ�һ��
	//�β��е����� ,���������������ָ�봦�� ����C���Ե���ɫ
	//���� ����Ҳ���� 
//3 �β�д�ں�����,��д�ں�������һ����,ֻ�����Ǿ��ж�������Զ���.
/*
void main22()
{
	int		i = 0,	j = 0;
	int		tmp = 0;
	int		num = 0;
	int a[] = {33,654,4,455,6,33,4,3333};
	num  = 7;

	num = sizeof(a)/sizeof(a[0]);
	printf("num:%d \n", num);

	printf("����֮ǰ\n");
	printArray(a, num);

	//����
	//���ѭ��	��i=0��ʱ��, ��j��1===N���б仯
	//���ѭ��	��i=1��ʱ��, ��j��2===N���б仯
	//			��i=2��ʱ��, ��j��3===N���б仯
	//����: ����һ������i����,������һ������j���б仯;��һ�� ���ν���
	sortArray(a, num);
	printf("����֮��\n");
	printArray(a, num);
	printf("hello...\n");
	system("pause");
}
*/
