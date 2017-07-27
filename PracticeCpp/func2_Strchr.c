
/*测试库函数 strchr*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc,char **argv)
{
	char ch1[20] = "Hello|World|!";
	char ch2[20];
	char *ch3;

	printf("sizeof(ch1) = %d\n",(int)sizeof(ch1));
	ch3 = (char *)malloc(sizeof(ch1));
	memset(ch3,0x00,sizeof(ch1));
	ch3 = strchr(ch1,'|');
	printf("strchred => ch3 = %s\n",ch3);	/*测试结果是：会返回一个指针，移动至字符串中指定的第一个字符之后*/


	return 0;
}
