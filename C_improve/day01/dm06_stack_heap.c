

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//��
char *getMem(int num)
{
	char *p1 = NULL;
	p1 = (char *)malloc(sizeof(char) * num);
	if (p1 == NULL)
	{
		return NULL;
	}
	return p1;
}

//ջ
//ע�� return���ǰ��ڴ�� 64���ֽ�,��return����,���ǰ��ڴ����׵�ַ(�ڴ�ı��0xaa11) ,���ظ� tmp

// ���ָ��Ĺؼ�,���ڴ�. û���ڴ������ָ�� 

//
char *getMem2()
{
	char buf[64]; //��ʱ���� ջ�����
	strcpy(buf, "123456789");
	//printf("buf:%s\n", buf);
	return buf;
}

void main61()
{
	char *tmp = NULL;
	tmp = getMem(10);
	if (tmp == NULL)
	{
		return ;
	}
	strcpy(tmp, "111222"); //��tmp��ָ����ڴ�ռ���copy����

	//tmp = getMem2();
	tmp = 0xaa11;

	printf("hello..tmp:%s.\n", tmp);
	system("pause");
	return ;
}