#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//һ��ָ��ĵ����÷�
//���� int a[10]
//�ַ��� 
//1 C���Ե��ַ��� �����β���ַ���
//2 ��C������û���ַ�������  ͨ���ַ����� ��ģ���ַ��� 
//3 �ַ������ڴ����  ���� ջ�� ȫ���� (����Ҫ)


//�ַ����� ��ʼ��
void main51()
{

	//1 ָ������  
	char buf2[100] = {'a', 'b', 'c', 'd'};  
	//1-1char buf3[2] = {'a', 'b', 'c', 'd'}; //�����ʼ���ĸ��������ڴ�ĸ��� �������
	//1-22//�����buf2[4]-buf2[99] 0


	//2 ��ָ������  C���������Զ������Ա ��Ԫ�صĸ���
	char buf1[] = {'a', 'b', 'c', 'd'};  //buf1��һ������ ����һ����0��β���ַ���

	printf("buf2: %s \n", buf2);

	printf("buf2[88]:%d \n", buf2[88]);

	printf("hello....\n");
	system("pause");

	return ;
}

//���ַ��� �� ��ʼ���ַ�����
//strlen() ���� ������0
//sizeof() �ڴ��Ĵ�С
void main52()
{
	int size = 0;
	char buf3[] = "abcd"; // buf3 ��Ϊ�ַ����� Ӧ����5���ֽ� //��Ϊ�ַ��� Ӧ��4���ֽ�

	int len = strlen(buf3);
	printf("buf3�ַ��ĳ���:%d \n", len); //4

	//buf3 ��Ϊ���� ������һ���������� ����(�̶�С���ڴ��ı���)
	size = sizeof(buf3); //
	printf("buf3������ռ�ڴ�ռ��С:%d \n", size); //5

	printf("hello....\n");

	{
		char buf4[128] = "abcd"; // buf
		printf("buf4[100]:%d \n", buf4[100]);
	}
	system("pause");
	return ;
}

//ͨ�������±� �� ָ��
void main58()
{
	int		i = 0;
	char	*p = NULL;
	char buf5[128] = "abcdefg"; // buf

	for (i=0; i<strlen(buf5); i++)
	{
		printf("%c ", buf5[i]); 
	}
	
	p = buf5; //buf ����������Ԫ�صĵ�ַ

	for (i=0; i<strlen(buf5); i++)
	{
		p = p +i;
		printf("%c ", *p ) ;
	}

	//buf
	for (i=0; i<strlen(buf5); i++)
	{
		printf("%c ", *(buf5+i) ) ;
	}

	//[] *���Ƶ�����
	// buf5[i] ===> buf5[0+i]; ==> *(buf5+i);

	{
		//buf5 = buf5 + 1;
		//buf5 = 0x11;
	}
	printf("hello....\n");
	system("pause");
}

// []�ı��� :��*p ��һ�� ,ֻ�����Ƿ��ϳ���Ա���Ķ�ϰ��
// buf5 ��һ��ָ��,  ֻ���ĳ���  buf5��һ������ָ��  �����ڴ��ʱ��,��֤buf��ָ����ڴ�ռ䰲ȫ�ͷ�
//Ϊʲô��ô��?

//p��ָͨ����ڴ��׵�ַ����



