#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//��ӡ  ���� 
//��װ�ɺ���
void main31()
{
	int i = 0, j = 0;
	int num = 4;
	char myBuf[30];
	char tmpBuf[30];
	char myArray[10][30] = {"aaaaaa", "ccccc", "bbbbbbb", "1111111111111"};

	//��ӡ 
	printf("����֮ǰ\n");
	for (i=0; i<num; i++)
	{
		printf("%s\n", myArray[i]);
	}

	for (i=0; i<num; i++)
	{
		for (j=i+1; j<num; j++)
		{
			if (strcmp (myArray[i],  myArray[j]) > 0)
			{
				strcpy(tmpBuf, myArray[i]);  //���������ڴ��
				strcpy(myArray[i], myArray[j]);
				strcpy(myArray[j], tmpBuf);
			}
		}
	}

	//��ӡ 
	printf("����֮��\n");
	for (i=0; i<num; i++)
	{
		printf("%s\n", myArray[i]);
	}


	printf("hello...\n");
	system("pause");
	return ;
}

//����ı����ǣ�dm03_����ָ��������_��2���ڴ�ģ�� �� myArray + 1
				// dm03_����ָ��������_��1���ڴ�ģ��   myArray + 1 ��һ�� ��
//ָ��Ĳ�����һ��  ָ����ָ����ڴ�ռ�������಻һ�� ��������
void printMyArray02_err(char **myArray, int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );  //
	}
}

void printMyArray02(char myArray[10][30], int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );  //
	}
}



//���������ڴ�顣��������������
void sortMyArray02(char myArray[10][30], int num)
{
	int i, j = 0;
	char tmpBuf[30];

	for (i=0; i<num; i++)
	{
		for (j=i+1; j<num; j++)
		{
			if (strcmp (myArray[i],  myArray[j]) > 0)
			{
				strcpy(tmpBuf, myArray[i]);  //���������ڴ��
				strcpy(myArray[i], myArray[j]);
				strcpy(myArray[j], tmpBuf);
			}
		}
	}

}

//��ӡ  ���� 
//��װ�ɺ���
void main333()
{
	int i = 0, j = 0;
	int num = 4;
	char myBuf[30];
	char tmpBuf[30];
	char myArray[10][30] = {"aaaaaa", "ccccc", "bbbbbbb", "1111111111111"};

	//myArray�� ������ֻ����ģ���10�� ��ÿ��30�С�����������ʲô��myArray+1  ��ά�������ı��ʣ�

	{
		int len1 = sizeof(myArray);
		int len2 = sizeof(myArray[0]);
		int size = len1/len2;
		printf("len1:%d , len2:%d  size:%d \n", len1, len2, size);

	}
	

	//��ӡ 
	printf("����֮ǰ\n");

	printMyArray02(myArray, num);
	

	sortMyArray02(myArray, num);

	//��ӡ 
	printf("����֮��\n");
	printMyArray02(myArray, num);

	printf("hello...\n");
	system("pause");
	return ;
}