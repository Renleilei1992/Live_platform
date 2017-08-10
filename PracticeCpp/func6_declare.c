


#include <stdio.h>
#include <string.h>
#include "DeclareCfg.h"

int main(int argc,char **argv)
{
	char sTemp[LEN_STR_MAX + 1];

	memset(sTemp, 0x00, sizeof(sTemp));
	memcpy(sTemp,"Hello world!:)",sizeof(sTemp) - 1);

	printf("[sTemp]=%s\n",sTemp);

	return 0;
}
