

#include <stdio.h>
#include <string.h>

#define CHANNEL_SGB "101"

int main(int argc,char **argv)
{
	int iRet = 0;
	char channel[3 + 1];

	printf("sizeof(channel)=[%d]\n",(int)sizeof(channel));    
	printf("sizeof(101)=[%d]\n",(int)sizeof("101"));

	memset(channel, 0x00, sizeof(channel));
	memcpy(channel, "100", sizeof(channel));

	printf("channel=[%s]\n",channel);
	iRet = memcmp(channel, CHANNEL_SGB, sizeof(channel));
	printf("iRet=[%d]\n",iRet);



	return 0;
}
