

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Ұָ�������ԭ��
//ָ�����������ָ����ڴ�ռ������������ͬ�ĸ���
// �ͷ���ָ�����µ��ڴ�ռ�  ����ָ���������û�����ó�null
//����ͷŵ�ʱ�� ͨ��if (p1 != NULL)

//���ⷽ���� 1������ָ���ʱ�� ��ʼ����nuLL 2���ͷ�ָ����ָ����ڴ�ռ�󣬰�ָ�����ó�NULL��
void main11()
{

	char  *p1 = NULL;
	p1 = (char *)malloc(100);
	if (p1 == NULL)
	{
		return ;
	}
	strcpy(p1, "11112222");

	printf("p1:%s \n", p1);

	if (p1 != NULL)
	{
		free(p1);
		p1 = NULL;
	}

	//

	if (p1 != NULL)
	{
		free(p1);
	}

	printf("hello...\n");
	system("pause");
	return ;
}
