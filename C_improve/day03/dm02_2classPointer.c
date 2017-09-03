#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main21()
{
	int		i = 0, j = 0;
	int		num = 0;
	char	*tmp = NULL;
	//数组 数组中的每一个元素是指针 指针数组
	char *myArray[] = {"aaaaaa", "ccccc", "bbbbbb", "111111"};

	//打印
	num = sizeof(myArray)/sizeof(myArray[0]);

	printf("排序之前\n");
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );
	}

	//排序
	for (i=0; i<num; i++)
	{
		for (j=i; j<num; j++)
		{
			if (strcmp(myArray[i], myArray[j]) > 0 )
			{
				tmp = myArray[i];  //注意  交换的是数组元素 交换的是指针的值
				myArray[i] = myArray[j];
				myArray[j] = tmp;
			}
		}
	}

	printf("排序之后\n");
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
	//排序
	for (i=0; i<num; i++)
	{
		for (j=i; j<num; j++)
		{
			if (strcmp(myArray[i], myArray[j]) > 0 )
			{
				tmp = myArray[i];  //注意  交换的是数组元素 交换的是指针的值 //改变指针的指向
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
	//数组 数组中的每一个元素是指针 指针数组
	char *myArray[] = {"aaaaaa", "ccccc", "bbbbbb", "111111"};

	//打印
	num = sizeof(myArray)/sizeof(myArray[0]);

	printf("排序之前\n");
	printMyArray11(myArray, num);


	sortMyArray11(myArray, num);


	printf("排序之后\n");
	printMyArray11(myArray, num);

	printf("hello...\n");
	system("pause");
	return ;
}