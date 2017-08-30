#include <stdio.h>
#include <string.h>

#define LEN_STAT 1

int main(int argc,char **argv)
{
	char sImgFlag[LEN_STAT + 1];
	memset(sImgFlag, 0x00, sizeof(sImgFlag));
	sImgFlag[0] = '1';

	printf("sImgFlag=[%s]\n", sImgFlag);

	return 0;
}
