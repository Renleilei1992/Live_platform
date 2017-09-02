#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*************************************
* ģ�����ƣ�int myTriNul(char *src)
* ģ�鹦�ܣ�ȥ���ַ����ո�
* ģ�����룺�ַ�����ַ
* ģ�������src ��������Ҳ�������ͨ����ַ�����ַ���
* �� �� ֵ��0 �ɹ� -1 ʧ��
* �� д �ˣ��Ž�
* �༭ʱ�䣺2017��7��27��16:51:48
* ��     ����v1.0
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

//��һ���ַ�������������������abcdef,acccd,eeee,aaaa,e3eeeee,sssss,";��

//�������ֵָ����� �� �����߼�֮��Ĺ�ϵ
int spitString(const char *buf1, char c, char buf2[10][30], int *count)
{
	//strcpy(buf2[0], "aaaaa");
	//strcpy(buf2[1], "bbbbbb");
	char *p=NULL, *pTmp = NULL;
	int	tmpcount = 0;

	//1 p��ptmp��ʼ��
	p = buf1;
	pTmp = buf1;
	do 
	{
		//2 ��������������λ�� p����  �γɲ�ֵ ���ַ���
		p = strchr(p, c);
		if (p != NULL)
		{
			if (p-pTmp > 0)
			{
				strncpy(buf2[tmpcount], pTmp,  p-pTmp);
				buf2[tmpcount][p-pTmp]  = '\0';  //�ѵ�һ�����ݱ�� C����ַ���
				tmpcount ++;
				//3���� ��p��ptmp�ﵽ��һ�μ���������
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
* ģ�����ƣ�int mySplitString(const char *src, char c, char ***des, int *len)
* ģ�鹦�ܣ���src ��ַָ����ַ��� ���� �ָ��� C �ָ�������ַ�������ŵ�des ָ���
*				�Ķ�ά������
* ģ�����룺src ��Ҫ�ָ���ַ�����ַ�� c �ָ��ʶ��
* ģ�������des ����ַ�����ĵ�ַ��
*              ��ά����ĵ�ַ������ָ�룬len ��ά�����а�����һά����ĸ������������
* �� �� ֵ��0 �ɹ� -1 ʧ��
* �� д �ˣ��� ��
* �༭ʱ�䣺2017��7��27��	16:51:48
* ��     ����v1.0
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

// ȥ���ַ������Ŀո�
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
* ģ�����ƣ�int myTrmLefNul(char *src)
* ģ�鹦�ܣ�ȥ���ַ�����ߵĿո�
* ģ�����룺�ַ�����ַ
* ģ�������
* ����ֵ  ��0 �ɹ� -1 ʧ��
* ��д��  ���Ž�
* �༭���ڣ�2017��7��27��17:14:59
* ��     ����v1.0
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
// ȥ���ַ����Ҳ�Ŀո�
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
* ģ�����ƣ�int myTriRigNul(char *src)
* ģ�鹦�ܣ�ȥ���ַ����ұߵĿո�
* ģ�����룺�ַ�����ַ
* ģ�������src ��������Ҳ�������ͨ����ַ�����ַ���
* ����ֵ��0 �ɹ� -1 ʧ��
* ��д�ˣ��Ž�
* �༭ʱ�䣺2017��7��27��16:51:48
* �汾  ��v1.0
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

// ȥ��ȫ���Ŀո�
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

// ʹ��putchar() �ݹ� �����ӡ �ַ���
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
//��ҵ �õ������ڴ�ģ���������
/*
int spitString2(const char *buf1, char c, char ***pp, int *count)
{
	
}

char ** spitString3(const char *buf1, char c, int *count)
{

}
*/




