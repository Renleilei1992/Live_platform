#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//char *p = "abcd111122abcd3333322abcd3333322qqq"; 
//���ַ���p�� abcd���ֵĴ���
//1���Զ��庯���ӿ�,����������� 50 // i++ ++ ++
//2 �Զ����ҵ���� �� main��������ֿ�  50

void main81()
{
	//strstr(str, str2)
	int ncount = 0;

	//��ʼ�� ��pָ��ﵽ���ҵ�����
	char *p = "11abcd111122abcd3333322abcd3333322qqq";  

	do 
	{
		p = strstr(p, "abcd");
		if (p != NULL)
		{
			ncount++; //
			p = p + strlen("abcd"); //ָ��ﵽ�´β��ҵ�����
		}
		else
		{
			break;
		}
	} while (*p != '\0');


	printf("ncount:%d \n", ncount);
	system("pause");
	return ;
}

void main88()
{
	int ncount = 0;

	//��ʼ�� ��pָ��ﵽ���ҵ�����
	char *p = "2abcd3333322qqqabcd";  
	while ( p = strstr(p, "abcd"))
	{
		ncount ++;
		p = p + strlen("abcd"); //��pָ��ﵽ���ҵ�����
		if (*p == '\0')
		{
			break;
		}
	}
	printf("ncount:%d \n", ncount);

	printf("hello...\n");
	system("pause");
}

//char *p = "abcd111122abcd3333322abcd3333322qqq"; 
//���ַ���p�� abcd���ֵĴ���
//1���Զ��庯���ӿ�,����������� 50 // i++ ++ ++
//2 �Զ����ҵ���� �� main��������ֿ�  50
int getCount(char *mystr /*in*/, char *sub /*in*/,int *ncount)
{
	int ret = 0;
	int tmpCount = 0;
	//��ʼ�� ��pָ��ﵽ���ҵ�����
	char *p = mystr; //��Ҫ���׸ı��βε�ֵ

	if (mystr==NULL || sub==NULL ||ncount==NULL)
	{
		ret = -1;
		printf("func getCount() err:%d (mystr==NULL || sub==NULL ||ncount==NULL) \n", ret);
		return ret;
	}

	do 
	{
		p = strstr(p, sub);
		if (p != NULL)
		{
			tmpCount++; //
			p = p + strlen(sub); //ָ��ﵽ�´β��ҵ�����
		}
		else
		{
			break;
		}
	} while (*p != '\0');

	*ncount = tmpCount; //��Ӹ�ֵ��ָ����ڵ��������
	return ret;
}

int main()
{
	int ret = 0;
	char *p = "abcd111122abcd3333322abcd3333322qqq"; 
	int count = 0;
	char sub[] = "abcd";

	ret = getCount(p,sub,  &count);
	if (ret != 0)
	{
		printf("func getCount() err:%d \n", ret);
		return ret;
	}

	ret = getCount(p,NULL,  &count);
	if (ret != 0)
	{
		printf("func getCount() err:%d \n", ret);
		return ret;
	}
	printf("count:%d \n", count);
	system("pause");
}