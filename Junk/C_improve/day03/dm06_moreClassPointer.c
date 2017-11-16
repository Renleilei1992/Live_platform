#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char **getMem51(int num)
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

int getMem52(char ***p3 , int num)
{
	int i = 0;
	char **tmp = NULL;

	if (p3 == NULL)
	{
		return -1;
	}
	
	tmp = (char **)malloc(sizeof(char *) * num);
	if (tmp == NULL)
	{
		return NULL;
	}

	for (i=0; i<num; i++)
	{
		tmp[i] = (char *)malloc(sizeof(char)  * 100  ); //char buf[100];
		sprintf(tmp[i], "%d%d%d", i+1, i+1, i+1);
	}
	*p3 = tmp; 
	//1 2

	return 0;
}

void getMem52_Free(char ***p3 , int num)
{
	int i = 0;
	char **tmp = NULL;

	if (p3 == NULL)
	{
		return ;
	}
	tmp = *p3; 

	for (i=0; i<num; i++)
	{
		free(tmp[i]);
	}
	free(tmp);
	 
	*p3 = NULL; //把实参赋值成null
}



void main66()
{
	int i = 0, j = 0;
	char **p2 = NULL;
	int num = 5;
	char *tmp = NULL;
	char tmpbuf[100];
	//p2 = getMem51(num);

	getMem52(&p2, num);

	for (i=0; i<num; i++)
	{
		printf("%s \n", p2[i]);
	}


	getMem52_Free(&p2, num);
	printf("hello...\n");
	system("pause");
	return ;
}