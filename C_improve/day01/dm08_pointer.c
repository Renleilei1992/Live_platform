#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main81()
{
	int a = 10;
	char *p1 = 100;  //����4���ֽڵ��ڴ�
	char ****p2 = 100;


	int *p3 = NULL;

	p3 = &a;

	*p3 = 20; //��ӵ��޸�a��ֵ
	//*����һ��Կ�� ͨ��һ����ַ(&a),ȥ�޸�a�����ı�ʾ���ڴ�ռ�

	{
		int c = 0;
		c = *p3;  //c=20
		//*p����=����� д�ڴ�
		//*p��=�ŵ��ұ� ���ڴ�
		printf("c:%d \n", c);
	}

	{
		char *p4 = NULL;
		p4 = (char *)malloc(100);
		p4 = (char *)malloc(200); //0xcc11

	}

	printf("a:%d , p1:%d , p2: %d", sizeof(a), sizeof(p1), sizeof(p2));
	printf("hello...\n");

	
	system("pause");
	return ;
}

char *getStr81()
{
	char *tmp = NULL;
	tmp = "abcdefgf";
	return tmp;
}

/*
int getABC1(char    *p1);  int getABC1(char*       p1);
int	getABC2(char **    p2);	int	getABC2(char *    *p2);   int	getABC2(char           **p2);
int	getABC3(char ***p3);
int	getABC4(char (*p4)[30]);  int	getABC4(char (*p4)            [30]);
int	getABC5(char p5[10][30]); int	getABC5(char p5[10][30]);

//ָ������������ �β��ж༶ָ���ʱ��, 
//վ�ڱ������ĽǶ� ,ֻ��Ҫ����4���ֽڵ��ڴ�(32bitƽ̨)
//������ʹ���ڴ��ʱ��,���ǲŹ���ָ����ָ����ڴ� ��һά�Ļ��Ƕ�ά��


*/


void main()
{
	char *p = getStr81();
	printf("p:%s \n", p);
	*(p+2) = 'r';  //�������ֵĴ��� ��ָ֤����ָ����ڴ�ռ� ���Ա��޸�
	system("pause");
	return ;
}