

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//return ֻ�ܷ���һ�����
//
int  getFileLen2()
{
	int a = 100;  
	return a;
}


int  getFileLen(int *p)
{
	*p = 41;  //  p��ֵ��a�ĵ�ַ *a�ĵ�ַ����޸�a��ֵ 
	//�ڱ����ú������� ͨ���β� ȥ ��ӵ��޸� ʵ�ε�ֵ...
}

//�βε�����
int  getFileLen3(int b)
{
	int  i = 0;
	b = 100;//  p��ֵ��a�ĵ�ַ *a�ĵ�ַ����޸�a��ֵ
}


//1��ָ��ļ�������
void main32()
{
	int a = 10;  //����1  ��������������(ʵ�� ����һ���������β�p)
	int *p = NULL;

	//�޸�a��ֵ
	a = 20; //ֱ���޸�

	p = &a;  //����2 ��������

	*p = 30; //p��ֵ��a�ĵ�ַ *����һ��Կ�� ͨ����ַ �ҵ�һ���ڴ�ռ� ���ӵ��޸���a��ֵ
	printf("a: %d \n", a);

	{
		*p = 40;  //  p��ֵ��a�ĵ�ַ *a�ĵ�ַ����޸�a��ֵ  //����3 *p
		printf("a: %d \n", a);
	}

	getFileLen(&a); //��������: ��ʵ��ȡ��ַ ���ݸ� �β�
	printf("getFileLen�� a: %d \n", a);
	getFileLen3(a);
	printf("getFileLen3�� a: %d \n", a);


	printf("hello...\n");
	system("pause");
	return ;
}

void getMem(char **p2)
{
	*p2 = 400; //��Ӹ�ֵ  p2��p1�ĵ�ַ
}

void getMem2(char *p2)
{
	p2 = 800; //��Ӹ�ֵ  p2��p1�ĵ�ַ
}

void main33()
{
	char *p1 = NULL;

	char **p2 = NULL;

	p1 = 0x11;
	p2 = 0x22;

	//ֱ���޸�p1��ֵ

	p1 = 0x111;

	//����޸�p1��ֵ
	p2 = &p1; 

	*p2 = 100; //��Ӹ�ֵ  p2��p1�ĵ�ַ

	printf("p1:%d \n", p1);

	{
		*p2 = 200; //��Ӹ�ֵ  p2��p1�ĵ�ַ
		printf("p1:%d \n", p1);
	}

	getMem(&p1);

	getMem2(p1);

	printf("p1:%d \n", p1);



	system("pause");
	return ;
}


int  getMem3(char **myp1, int *mylen1,  char **myp2, int *mylen2)
{
	int		ret = 0;
	char	*tmp1, *tmp2;

	tmp1 = (char *)malloc(100);
	strcpy(tmp1, "1132233");

	//��Ӹ�ֵ 
	*mylen1 = strlen(tmp1);  //1��ָ��
	*myp1 = tmp1; //2��ָ��ļ�Ӹ�ֵ

	tmp2 = (char *)malloc(200);
	strcpy(tmp2, "aaaaavbdddddddd");

	*mylen2 = strlen(tmp2);  //1��ָ��
	*myp2 = tmp2; //2��ָ��ļ�Ӹ�ֵ


	return ret;
}

int  main35()
{
	int		ret = 0;
	char	*p1 = NULL;
	int		len1 = 0;
	char	*p2 = NULL;
	int		len2 = 0; 

	ret = getMem3(&p1, &len1, &p2, &len2);
	if (ret != 0)
	{
		printf("func getMem3() err:%d \n", ret);
		return ret;
	}
	printf("p1:%s \n", p1);
	printf("p2:%s \n", p2);
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


	printf("p1:%d \n", p1);
	system("pause");
	return ret;
}


/* ��Ӹ�ֵ��������������
	����1  //����1��������ʵ�Σ� //����1���������βΣ�
	����2//������������ʵ��ȡ��ַ�����β�
	����3��//*�β�ȥ��ӵص��޸���ʵ�ε�ֵ��
	*/

//��Ӹ�ֵ��Ӧ�ó���
void main37()
{
	//1 2 3 ��3������ д����һ������
	//12 д��һ��   3 ����д������һ����������  =====>��������
	//1         23д��һ�� ===>��ש ====C++����,��ʱ��,�����ʶ......
	char from[128];
	char to[128] = {0};
	char *p1 = from;
	char *p2 = to;

	strcpy(from, "1122233133332fafdsafas");

	while (*p1 != '\0')
	{
		*p2 = *p1;
		p2 ++;
		p1++;
	}

	printf("to:%s \n", to);
	
	system("pause");
	return ;

}