#include <stdio.h>

int main(int argc,char **argv)
{
	char str[11] = {};
	int num = sizeof(str);
	snprintf( str, sizeof(str)-1, "01234567%d9101112", 8);
	printf("sizeof(str)=[%d],str=[%s]\n",num,str);

	return 0;
}
