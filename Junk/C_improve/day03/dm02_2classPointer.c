#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main21()
{
	int		i = 0, j = 0;
	int		num = 0;
	char	*tmp = NULL;
	//���� �����е�ÿһ��Ԫ����ָ�� ָ������
	char *myArray[] = {"aaaaaa", "ccccc", "bbbbbb", "111111"};

	//��ӡ
	num = sizeof(myArray)/sizeof(myArray[0]);

	printf("����֮ǰ\n");
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );
	}

	//����
	for (i=0; i<num; i++)
	{
		for (j=i; j<num; j++)
		{
			if (strcmp(myArray[i], myArray[j]) > 0 )
			{
				tmp = myArray[i];  //ע��  ������������Ԫ�� ��������ָ���ֵ
				myArray[i] = myArray[j];
				myArray[j] = tmp;
			}
		}
	}

	printf("����֮��\n");
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );
	}

	printf("hello...\n");
	system("pause");
	return ;
}


void printMyArray11(char **myArray, int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );
	}
}

void sortMyArray11(char **myArray, int num)
{
	int i =0 , j = 0;
	char *tmp = NULL;
	//����
	for (i=0; i<num; i++)
	{
		for (j=i; j<num; j++)
		{
			if (strcmp(myArray[i], myArray[j]) > 0 )
			{
				tmp = myArray[i];  //ע��  ������������Ԫ�� ��������ָ���ֵ //�ı�ָ���ָ��
				myArray[i] = myArray[j];
				myArray[j] = tmp;
			}
		}
	}
}

void main211()
{
	int		i = 0, j = 0;
	int		num = 0;
	char	*tmp = NULL;
	//���� �����е�ÿһ��Ԫ����ָ�� ָ������
	char *myArray[] = {"aaaaaa", "ccccc", "bbbbbb", "111111"};

	//��ӡ
	num = sizeof(myArray)/sizeof(myArray[0]);

	printf("����֮ǰ\n");
	printMyArray11(myArray, num);


	sortMyArray11(myArray, num);


	printf("����֮��\n");
	printMyArray11(myArray, num);

	printf("hello...\n");
	system("pause");
	return ;
}