#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*************************************
* 模块名称：int myTriNul(char *src)
* 模块功能：去除字符串空格
* 模块输入：字符串地址
* 模块输出：src 既是输入也是输出，通过地址操作字符串
* 返 回 值：0 成功 -1 失败
* 编 写 人：张健
* 编辑时间：2017年7月27日16:51:48
* 版     本：v1.0
*************************************/
int myTriNul(char *src)
{
	int ret = 0;
	char *tmp = NULL;
	tmp = src;
	if (NULL == src)
	{
		ret = -1;
		printf("func:myTriNul error: %d\n", ret);
		return ret;
	}
	ret = myTrmLefNul(tmp);
	if (ret != 0)
	{
		ret = -2;
		printf("func:myTriNul error: %d\n", ret);
		return ret;
	}
	ret = myTriRigNul(tmp);
	if (ret != 0)
	{
		ret = -3;
		printf("func:myTriNul error: %d\n", ret);
		return ret;
	}
	return ret;
}

//有一个字符串符合以下特征（”abcdef,acccd,eeee,aaaa,e3eeeee,sssss,";）

//分清楚赋值指针变量 和 操作逻辑之间的关系
int spitString(const char *buf1, char c, char buf2[10][30], int *count)
{
	//strcpy(buf2[0], "aaaaa");
	//strcpy(buf2[1], "bbbbbb");
	char *p=NULL, *pTmp = NULL;
	int	tmpcount = 0;

	//1 p和ptmp初始化
	p = buf1;
	pTmp = buf1;
	do 
	{
		//2 检索符合条件的位置 p后移  形成差值 挖字符串
		p = strchr(p, c);
		if (p != NULL)
		{
			if (p-pTmp > 0)
			{
				strncpy(buf2[tmpcount], pTmp,  p-pTmp);
				buf2[tmpcount][p-pTmp]  = '\0';  //把第一行数据变成 C风格字符串
				tmpcount ++;
				//3重新 让p和ptmp达到下一次检索的条件
				pTmp = p = p + 1;
			}
		}
		else
		{
			break;
		}
	} while (*p!='\0');
	
	*count = tmpcount;
	return 0;
}
/*************************************
* 模块名称：int mySplitString(const char *src, char c, char ***des, int *len)
* 模块功能：将src 地址指向的字符串 根据 分隔符 C 分割成若干字符串，存放到des 指向的
*				的二维数组中
* 模块输入：src 需要分割的字符串地址， c 分割标识符
* 模块输出：des 输出字符数组的地址，
*              二维数组的地址是三级指针，len 二维数组中包含的一维数组的个数，用于输出
* 返 回 值：0 成功 -1 失败
* 编 写 人：张 健
* 编辑时间：2017年7月27日	16:51:48
* 版     本：v1.0
*************************************/

int main7112()
{
	int ret = 0, i = 0;
	char *p1 = "abcdef,acccd,eeee,aaaa,e3eeeee,sssss,";
	char cTem= ',';
	int nCount;

	char myArray[10][30];

	ret = spitString(p1, cTem, myArray, &nCount);
	if (ret != 0)
	{
		printf("fucn spitString() err: %d \n", ret);
		return ret;
	}
	for (i=0; i<nCount; i++ )
	{
		printf("%s \n", myArray[i]);
	}
	printf("hello...\n");
	system("pause");
	return ret;
}

// 去除字符串左侧的空格
int delLefNul(char* src)
{
	int ret = 0;
	char* tmp = NULL; 
	if (src == NULL)
	{
		ret = -1;
		printf("func : delLefNul() err : %d ", ret);
		return ret;
	}
	tmp = src;
	while (*tmp == ' ')
	{
		tmp++;
	}
	strcpy(src, tmp);
	return ret;
}
/***************************************
* 模块名称：int myTrmLefNul(char *src)
* 模块功能：去除字符串左边的空格
* 模块输入：字符串地址
* 模块输出：
* 返回值  ：0 成功 -1 失败
* 编写人  ：张健
* 编辑日期：2017年7月27日17:14:59
* 版     本：v1.0
*
*************************************/
int myTrmLefNul(char *src)
{
	int ret = 0;
	char *tmp = NULL;
	if (NULL == src)
	{
		ret = -1;
		printf("func: myTrmLefNul() err! ret: %d", ret);
		return ret;
	}
	tmp = src;
	while (*tmp == ' ')
	{
		tmp++;
	}
	strcpy(src, tmp);

	return ret;
}

/**************************************/
// 去除字符串右侧的空格
int delRigNul(char* src)
{
	int ret = 0;
	char* pTmp = NULL;
	int len = strlen(src);
	pTmp = src + len - 1;
	if (NULL == src)
	{
		ret = -1;
		printf("func: delRigNul() err! ret: %d", ret);
		return ret;
	}
	while (*pTmp == ' ')
	{
		pTmp--;
	}
	*(++pTmp) = '\0';
	return ret;
}

/*************************************
* 模块名称：int myTriRigNul(char *src)
* 模块功能：去除字符串右边的空格
* 模块输入：字符串地址
* 模块输出：src 既是输入也是输出，通过地址操作字符串
* 返回值：0 成功 -1 失败
* 编写人：张健
* 编辑时间：2017年7月27日16:51:48
* 版本  ：v1.0
*************************************/
int myTriRigNul(char *src)
{
	int ret = 0;
	char *tmp = NULL;
	int len = 0;
	if (NULL == src)
	{
		ret = -1;
		printf("func:myTriRigNul src is null :d \n", ret);
	}
	len = strlen(src);
	tmp = src + len - 1;
	while (*tmp == ' ')
	{
		tmp--;
	}
	*(++tmp) = '\0';
	return ret;
}

// 去除全部的空格
int strTrim(char* pStr)
{
	int ret = 0;
	char *pTmp = pStr;
	char *p = pStr;
	int len = strlen(pStr);
	if (pStr == NULL)
	{
		ret = -1;
		printf("func : strTrim() err : %d ", ret);
		return ret;
	}
	while (*pStr != '\0')
	{
		if (*pStr != ' ')
		{
			*pTmp = *pStr;
			pTmp++;
		}
		pStr++;
	}
	*pTmp = '\0';
	memset(++pTmp, 0, len - strlen(p));
	return ret ;
}

// 使用putchar() 递归 逆序打印 字符串
void rePrint(char *str)
{
	if (*str == '\0')
		return;
	//str++;
	rePrint(++str);
	//str--;
	putchar(*(--str));
}

void main17()
{
	int ret = 0;
	char a[30] = "   adf  ab  sdf  sf  435 ";
	//ret = delLefNul(a);
	ret = strTrim(a);
	if (ret != 0)
	{
		printf("func : delLefNul() err : %d ", ret);
		return ret ;
	}
	printf("%s \n", a);
	rePrint(a);
	printf("\n hello...\n");
	system("pause");
	return ret ;
}

void main()
{
	int ret = 0;
	char a[30] = "   adfabsdfsf435     ";
	//ret = delLefNul(a);
	ret = myTriNul(a);
	if (ret != 0)
	{
		printf("func : delRigNul() err : %d ", ret);
		return ret;
	}
	printf("%s \n", a);
	rePrint(a);
	printf("\n hello...\n");
	system("pause");
	return ret;
}
//作业 用第三种内存模型求解问题
/*
int spitString2(const char *buf1, char c, char ***pp, int *count)
{
	
}

char ** spitString3(const char *buf1, char c, int *count)
{

}
*/




