#include "stdlib.h"
#include "string.h"
#include "stdio.h"
//排序
void main()
{
	int	i = 0,j = 0;
	int	tmp = 0;
	int a[] = {6,5,4,7,3,1,2};
	printf("排序之前\n");
	for (i=0; i<7; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");	
	//排序
	//外层循环	当i=0的时候, 让j从1===N进行变化
	//外层循环	当i=1的时候, 让j从2===N进行变化
	//			当i=2的时候, 让j从3===N进行变化
	//结论: 按照一个变量i不变,让另外一个变量j进行变化;下一轮 依次进行
	for(i=0; i<7; i++)  
	{
		for (j=i+1; j<7; j++)  //内层循环: a[i] 和 a[j]比较
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
	printf("排序之后\n");
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
	//实参的a 和 形参的a 的数据类型本质不一样
	//形参中的数组 ,编译器会把它当成指针处理 这是C语言的特色
	for(i=0; i<num; i++) 
	{
		for (j=i+1; j<num; j++)  //内层循环: a[i] 和 a[j]比较
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
//数组做函数参数的退回问题  退回为一个指针, 
//1 正确做法：把数组的内存首地址和数组的有效长度传给被调用函数
//2 //实参的a 和 形参的a 的数据类型本质不一样
	//形参中的数组 ,编译器会把它当成指针处理 这是C语言的特色
	//排序 本质也剖析 
//3 形参写在函数上,和写在函数内是一样的,只不过是具有对外的属性而已.
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

	printf("排序之前\n");
	printArray(a, num);

	//排序
	//外层循环	当i=0的时候, 让j从1===N进行变化
	//外层循环	当i=1的时候, 让j从2===N进行变化
	//			当i=2的时候, 让j从3===N进行变化
	//结论: 按照一个变量i不变,让另外一个变量j进行变化;下一轮 依次进行
	sortArray(a, num);
	printf("排序之后\n");
	printArray(a, num);
	printf("hello...\n");
	system("pause");
}
*/
