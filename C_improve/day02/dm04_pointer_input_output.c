#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//
int  getMem41(char **myp1/*out*/ , int *mylen1 /*out*/,  char **myp2 /*out*/, int *mylen2 /*out*/)
{
	int		ret = 0;
	char	*tmp1, *tmp2;

	tmp1 = (char *)malloc(100);
	strcpy(tmp1, "1132233");

	//间接赋值 
	*mylen1 = strlen(tmp1);  //1级指针
	*myp1 = tmp1; //2级指针的间接赋值

	tmp2 = (char *)malloc(200);
	strcpy(tmp2, "aaaaavbdddddddd");

	*mylen2 = strlen(tmp2);  //1级指针
	*myp2 = tmp2; //2级指针的间接赋值


	return ret;
}

char *  getMem42(int num)
{
	int		ret = 0;
	char	*tmp1;

	tmp1 = (char *)malloc(num);
	strcpy(tmp1, "1132233");

	return tmp1;
}



int  main44()
{
	int		ret = 0;
	char	*p1 = NULL;
	int		len1 = 0;
	char	*p2 = NULL;
	int		len2 = 0; 

	ret = getMem41(&p1, &len1, &p2, &len2);
	if (ret != 0)
	{
		printf("func getMem41() err:%d \n", ret);
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

	p1 = getMem42(100);
	printf("p1:%s \n", p1);
	if (p1 != NULL)
	{
		free(p1);
		p1 = NULL;
	}



	printf("p1:%d \n", p1);
	system("pause");
	return ret;
}
