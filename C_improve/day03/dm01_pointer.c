#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
//指针做输出：被调用函数分配内存  -----OK
//指针做输入：主调用函数 分配内存
//求文件中的两段话的长度
int getMem(char **myp1, int *mylen1, char **myp2, int *mylen2)
{
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	tmp1 = (char *)malloc(100);
	if (tmp1 == NULL)
	{
		return -1;
	}
	strcpy(tmp1, "abcdefg");
	*mylen1 = strlen(tmp1);

	*myp1 = tmp1; //间接修改实参p1的值

	tmp2 = (char *)malloc(100);
	if (tmp2 == NULL)
	{
		return -2;
	}
	strcpy(tmp2, "11122233333");
	*mylen2 = strlen(tmp2);

	*myp2 = tmp2; //间接修改实参p1的值
	return 0;
}

int getMem_Free(char **myp1)
{
	/*
	if (myp1 == NULL)
	{
		return ;
	}
	free(*myp1);  //释放完指针变量 所致的内存空间
	*myp1 = NULL;  //把实参修改成nULL
	*/
	char *tmp = NULL;
	if (myp1 == NULL)
	{
		return -1;
	}
	tmp = *myp1;
	free(tmp);  //释放完指针变量 所致的内存空间
	*myp1 = NULL;  //把实参修改成nULL
	return 0;
}


void main11()
{
	char  *p1 = NULL;
	int len1 = 0;

	char *p2 = NULL;
	int len2 = 0;

	int ret = 0;

	ret  = getMem(&p1, &len1, &p2, &len2 );

	printf("p1: %s \n", p1);
	printf("p2: %s \n", p2);

	getMem_Free(&p1);
	getMem_Free(&p2);  

	system("pause");
	return ;
}

int getMem_Free0(char *myp1)
{
	if (myp1 == NULL)
	{
		return -1;
	}
	free(myp1);  //释放完指针变量 所致的内存空间

	myp1 = NULL;

	return 0;
}

void main12()
{
	char  *p1 = NULL;
	int len1 = 0;

	char *p2 = NULL;
	int len2 = 0;

	int ret = 0;

	ret  = getMem(&p1, &len1, &p2, &len2 );

	printf("p1: %s \n", p1);
	printf("p2: %s \n", p2);

	if (p1 != NULL)
	{
		free(p1);
		p1 = NULL;
	}
	if (p2 != NULL)
	{
		free(p2);
		p2 = NULL;
	}

	getMem_Free0(p1);  //在被调用函数中  把p1所指向的内存给释放掉 ，但是 实参p1不能被修改成NULLL 有野指针现象
	getMem_Free0(p2);  

	system("pause");
	return ;
}