
/*此程序对Linux自带的标准库函数进行测试*/

#include <stdio.h>
#include <string.h>

char * GetStrItem(char *dest, char *src, char ch, unsigned int index);


int main(int argc,char **argv)
{
	char *test = "12|345|6789|101112131415";
	char ret[8];
	char ret1[12];

	printf("12|345|6789 's sizeof = %d\n",(int)sizeof(test));
	memset(ret, 0, sizeof(test));
	memset(ret1, 0, sizeof(test));
	GetStrItem(ret1,test,'|',3);
	printf("ret = %s\n",ret1);

	return 0;
}

char * GetStrItem(char *dest, char *src, char ch, unsigned int index)
{
	unsigned int i;
	int len;
	const char * p, * q;
	
	for(i = 0, p = src; i < index; ++i, ++p){
		printf("src's char = %s\n",p);
		if((p = strchr(p,ch)) == NULL){
			return NULL;
		}
	}
	printf("src's char = %s\n",p);
	q = strchr(p, ch);
	printf("q's char = %s\n",q);
	len = ((q == NULL) ? strlen(p) : q - p);
	printf("len = %d\n",len);
	memset(dest, 0, len+1);
	memcpy(dest, p, len);

	return dest;
}
