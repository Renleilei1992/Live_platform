#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//
void main41()
{
	int i = 0, j = 0;
	char **p2 = NULL;
	int num = 5;
	char *tmp = NULL;
	char tmpbuf[100];
	p2 = (char **)malloc(sizeof(char *) * num);

	for (i=0; i<num; i++)
	{
		p2[i] = (char *)malloc(sizeof(char)  * 100  ); //char buf[100];
		sprintf(p2[i], "%d%d%d", i+1, i+1, i+1);
	}

	//����֮ǰ 
	printf("����֮ǰ\n");
	for (i=0; i<num; i++)
	{
		printf("%s \n", p2[i]);
	}


	//���� �������� ��ָ��
	/*
	for (i=0; i<num; i++)
	{
		for (j=i+1; j<num; j++)
		{
			if (strcmp( p2[i] , p2[j]) < 0)
			{
				tmp = p2[i];
				p2[i] = p2[j];
				p2[j] = tmp;
			}
		}
	}
	*/

	//���� ������ʱ���ڴ�
	
	for (i=0; i<num; i++)
	{
		for (j=i+1; j<num; j++)
		{
			if (strcmp( p2[i] , p2[j]) < 0)
			{
				strcpy(tmpbuf, p2[i]);
				strcpy( p2[i], p2[j]);
				strcpy( p2[j], tmpbuf);
			}
		}
	}
	

	//����֮ǰ 
	printf("����֮��\n");
	for (i=0; i<num; i++)
	{
		printf("%s \n", p2[i]);
	}

	//�ͷ��ڴ�
	for(i=0; i<num; i++)
	{
		if (p2[i] != NULL)
		{
			free(p2[i]);
			p2[i] = NULL;
		}
	}

	if (p2!=NULL) 
	{
		free(p2);
	}


	printf("hello...\n");
	system("pause");
	return ;
}

//

//
char **getMem41(int num)
{
	int i = 0;
	char **p2 = NULL;
	p2 = (char **)malloc(sizeof(char *) * num);
	if (p2 == NULL)
	{
		return NULL;
	}

	for (i=0; i<num; i++)
	{
		p2[i] = (char *)malloc(sizeof(char)  * 100  ); //char buf[100];
		sprintf(p2[i], "%d%d%d", i+1, i+1, i+1);
	}
	return p2;
}





void printMyArray03(char **myArray, int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		//printf("%s \n", myArray[i]);
		printf("%s \n", *(myArray+i) );
	}
}

void sortMyArray03(char **myArray, int num)
{
	int i =0 , j = 0;
	char *tmp = NULL;
	//����
	for (i=0; i<num; i++)
	{
		for (j=i; j<num; j++)
		{
			if (strcmp(myArray[i], myArray[j]) > 0 )
			{
				tmp = myArray[i];  //ע��  ������������Ԫ�� ��������ָ���ֵ //�ı�ָ���ָ��
				myArray[i] = myArray[j];
				myArray[j] = tmp;
			}
		}
	}
}

void getMem41_Free(char **p2, int num)
{
	int i = 0;
	//�ͷ��ڴ�
	for(i=0; i<num; i++)
	{
		if (p2[i] != NULL)
		{
			free(p2[i]);
			p2[i] = NULL;
		}
	}

	if (p2!=NULL) 
	{
		free(p2);
	}

}


void main444()
{
	int i = 0, j = 0;
	char **p2 = NULL;
	int num = 5;
	char *tmp = NULL;
	char tmpbuf[100];
	p2 = getMem41(num);


	//����֮ǰ 
	printf("����֮ǰ\n");
	printMyArray03(p2, num);

	sortMyArray03(p2, num);

	//���� �������� ��ָ��
	/*
	for (i=0; i<num; i++)
	{
		for (j=i+1; j<num; j++)
		{
			if (strcmp( p2[i] , p2[j]) < 0)
			{
				tmp = p2[i];
				p2[i] = p2[j];
				p2[j] = tmp;
			}
		}
	}
	*/
	

	//����֮ǰ 
	printf("����֮��\n");
	printMyArray03(p2, num);

	getMem41_Free(p2,  num); //p2��һ��Ұָ��

	

	printf("hello...\n");
	system("pause");
	return ;
}