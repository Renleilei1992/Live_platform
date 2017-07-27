
/*测试?: 表达式*/
/*<表达式1>?<表达式2>:<表达式3>*/
/*若表达式1为真，则返回表达式2的值，若表达式1为假则返回表达式3的值*/

#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
	int a = 1;
	int b = 2;
	int c = 3;

	int val = a<b ? a<b : c-a;		//a<b 的值为1,
	printf("val = %d\n", val);


	return 0;
}
