#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//打印  排序 
//封装成函数
void main31()
{
	int i = 0, j = 0;
	int num = 4;
	char myBuf[30];
	char tmpBuf[30];
	char myArray[10][30] = {"aaaaaa", "ccccc", "bbbbbbb", "1111111111111"};

	//打印 
	printf("排序之前\n");
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
				strcpy(tmpBuf, myArray[i]);  //交换的是内存块
				strcpy(myArray[i], myArray[j]);
				strcpy(myArray[j], tmpBuf);
			}
		}
	}

	//打印 
	printf("排序之后\n");
	for (i=0; i<num; i++)
	{
		printf("%s\n", myArray[i]);
	}


	printf("hello...\n");
	system("pause");
	return ;
}

//问题的本质是：dm03_二级指针做输入_第2种内存模型 的 myArray + 1
				// dm03_二级指针做输入_第1种内存模型   myArray + 1 不一样 ；
//指针的步长不一样  指针所指向的内存空间的数据类不一样 。。。。
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



//交换的是内存块。。。。。。。。
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
				strcpy(tmpBuf, myArray[i]);  //交换的是内存块
				strcpy(myArray[i], myArray[j]);
				strcpy(myArray[j], tmpBuf);
			}
		}
	}

}

//打印  排序 
//封装成函数
void main333()
{
	int i = 0, j = 0;
	int num = 4;
	char myBuf[30];
	char tmpBuf[30];
	char myArray[10][30] = {"aaaaaa", "ccccc", "bbbbbbb", "1111111111111"};

	//myArray： 编译器只会关心：有10行 ，每行30列。。。。。干什么？myArray+1  多维数组名的本质，

	{
		int len1 = sizeof(myArray);
		int len2 = sizeof(myArray[0]);
		int size = len1/len2;
		printf("len1:%d , len2:%d  size:%d \n", len1, len2, size);

	}
	

	//打印 
	printf("排序之前\n");

	printMyArray02(myArray, num);
	

	sortMyArray02(myArray, num);

	//打印 
	printf("排序之后\n");
	printMyArray02(myArray, num);

	printf("hello...\n");
	system("pause");
	return ;
}