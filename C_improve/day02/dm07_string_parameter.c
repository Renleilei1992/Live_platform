#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main71()
{
	char a[] = "i am a student";
	char b[64];
	int  i = 0;

	for (i=0; *(a+i) != '\0'; i++)
	{
		*(b+i) = *(a+i);
	}

	//0û��copy��b��buf��.

	b[i] = '\0'; //��Ҫ
	printf("a:%s \n", a);
	printf("b:%s \n", b);

	system("pause");
	return ;
}

//�ַ���copy������������

//�ַ���copy����

//form�β� �β�to ��ֵ ��ͣ���ڱ仯....
//���ϵ��޸���from��to��ָ��
void copy_str21(char *from, char *to)
{
	for (; *from!='\0'; from++, to++)
	{
		 *to = *from;
	}
	*to = '\0';

	return ;
}

//*���� ��++�Ĳ���
//++ ���ȼ��� 
void copy_str22(char *from, char *to)
{
	for (; *from!='\0';)
	{
		*to++ = *from++;  //  �� *to = *from;  ��from++, to++ 
	}
	*to = '\0'; //

	return ;
}

void copy_str23(char *from, char *to)
{
	while( (*to = *from) != '\0' )
	{
		from ++; 
		to ++;
	}
}

void copy_str24(char *from , char *to)
{
	while ( (*to++ = *from++) != '\0')
	{
		;
	}
}


void copy_str25(char *from , char *to)
{
	//*(0) = 'a';
	while ( (*to++ = *from++) )
	{
		;
	}
}


void copy_str25_err(char *from , char *to)
{
	//*(0) = 'a';
	while ( (*to++ = *from++) )
	{
		;
	}

	printf("from:%s \n", from);
	
}


//��Ҫ���׸ı��βε�ֵ, Ҫ����һ��������ָ�����. ���βθ��ӹ���.....
int copy_str26_good(char *from , char *to)
{
	//*(0) = 'a';
	char *tmpfrom = from;
	char *tmpto = to;
	if ( from == NULL || to == NULL)
	{
		return -1;
	}


	while ( *tmpto++ = *tmpfrom++ ) ;  //�����

	printf("from:%s \n", from);
		
}

int main111()
{
	int ret = 0;
	char *from = "abcd";
	char buf2[100]; 
	//copy_str21(from, buf2);
	//copy_str22(from,buf2);
	//copy_str23(from, buf2);
	//copy_str24(from, buf2);
	//copy_str25(from ,buf2);
	//printf("buf2:%s \n", buf2);

	{
		//������
		char *myto = NULL;  //Ҫ�����ڴ�
		//copy_str25(from,myto );
	}
	{
		char *myto = NULL;  //Ҫ�����ڴ�
		
		ret = copy_str26_good(from, myto);
		if (ret != 0)
		{
			printf("func copy_str26_good() err:%d  ", ret);
			return ret;
		}
	}
	system("pause");
	return ret;
}


int main777()
{
	int ret = 0;
	char *from = "abcd";
	char buf2[100]; 

	printf("copy_str25_err begin\n");
	copy_str25_err(from, buf2);
	copy_str26_good(from, buf2);
	printf("copy_str25_err end\n");
	return 0;
}
