

#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//return 只能返回一个结果
//
int  getFileLen2()
{
	int a = 100;  
	return a;
}


int  getFileLen(int *p)
{
	*p = 41;  //  p的值是a的地址 *a的地址间接修改a的值 
	//在被调用函数里面 通过形参 去 间接的修改 实参的值...
}

//形参的属性
int  getFileLen3(int b)
{
	int  i = 0;
	b = 100;//  p的值是a的地址 *a的地址间接修改a的值
}


//1级指针的技术推演
void main32()
{
	int a = 10;  //条件1  定义了两个变量(实参 另外一个变量是形参p)
	int *p = NULL;

	//修改a的值
	a = 20; //直接修改

	p = &a;  //条件2 建立关联

	*p = 30; //p的值是a的地址 *就像一把钥匙 通过地址 找到一块内存空间 求间接的修改了a的值
	printf("a: %d \n", a);

	{
		*p = 40;  //  p的值是a的地址 *a的地址间接修改a的值  //条件3 *p
		printf("a: %d \n", a);
	}

	getFileLen(&a); //建立关联: 把实参取地址 传递给 形参
	printf("getFileLen后 a: %d \n", a);
	getFileLen3(a);
	printf("getFileLen3后 a: %d \n", a);


	printf("hello...\n");
	system("pause");
	return ;
}

void getMem(char **p2)
{
	*p2 = 400; //间接赋值  p2是p1的地址
}

void getMem2(char *p2)
{
	p2 = 800; //间接赋值  p2是p1的地址
}

void main33()
{
	char *p1 = NULL;

	char **p2 = NULL;

	p1 = 0x11;
	p2 = 0x22;

	//直接修改p1的值

	p1 = 0x111;

	//间接修改p1的值
	p2 = &p1; 

	*p2 = 100; //间接赋值  p2是p1的地址

	printf("p1:%d \n", p1);

	{
		*p2 = 200; //间接赋值  p2是p1的地址
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

	//间接赋值 
	*mylen1 = strlen(tmp1);  //1级指针
	*myp1 = tmp1; //2级指针的间接赋值

	tmp2 = (char *)malloc(200);
	strcpy(tmp2, "aaaaavbdddddddd");

	*mylen2 = strlen(tmp2);  //1级指针
	*myp2 = tmp2; //2级指针的间接赋值


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


/* 间接赋值成立的三个条件
	条件1  //定义1个变量（实参） //定义1个变量（形参）
	条件2//建立关联：把实参取地址传给形参
	条件3：//*形参去间接地的修改了实参的值。
	*/

//间接赋值的应用场景
void main37()
{
	//1 2 3 这3个条件 写在有一个函数
	//12 写在一块   3 单独写在另外一个函数里面  =====>函数调用
	//1         23写在一块 ===>抛砖 ====C++会有,到时候,你别不认识......
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