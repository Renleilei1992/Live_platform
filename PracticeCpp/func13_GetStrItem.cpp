
/*

函数功能: 取字符串中被分隔符分割的项目
	      例如在字符串"12|345|6789" 中取偏移为1的项，结果为"345",以"|"为分隔符
输入参数: src 	- 源字符串
		  ch  	- 分隔符
		  index - 项目的偏移值(从0开始)
输出参数: dest	- 目标单(应保证缓冲区足够大)
返回值  : NULL  - 未找到指定偏移值的项
		  非NULL- 目标串
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * GetStrItem(char *dest, const char *src, char ch, unsigned int index);

int main(int argc,char **argv)
{
	const char *src_str = "12|345|6789";
	
	char *Ret = (char *)malloc(sizeof(src_str));
	
	printf("strlen of src_str = [%d]\n", (int )strlen(src_str));
	printf("size   of src_str = [%d]\n", (int )sizeof(src_str));
	memset(Ret, 0x00, strlen(src_str));
	printf("memset over!\n");
    GetStrItem(Ret, src_str, '|', 1);

	printf("Ret = [%s]\n", Ret);
	printf("Ret's size   = [%d]\n", (int )sizeof(Ret));
	printf("Ret's strlen = [%d]\n", (int )strlen(Ret));
	int len = (int )strlen(Ret);
	for(int i = 0; i < len; i++, Ret++)
	{
		printf("Ret[%d] = [%s] ;   strlen(Ret) = [%d]\n", i, Ret, (int )strlen(Ret));
	}


	return 0;
}


char * GetStrItem(char *dest, const char *src, char ch, unsigned int index)
{
	unsigned int i = 0;
	int len = 0;
	const char *p, *q;
	
	for(i=0, p=src; i<index; i++, p++)
	{
		if((p = strchr(p,ch)) == NULL)
			return NULL;
	}
	
	q = strchr(p, ch);
	
	len = ((q == NULL) ? strlen(p) : q - p);
	memset(dest, 0x00, len + 1);
	memcpy(dest, p, len);

	return dest;
}


