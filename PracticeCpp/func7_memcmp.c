

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
	memcpy(channel, CHANNEL_SGB, sizeof(channel));

	printf("channel=[%s]\n",channel);
	iRet = memcmp(channel, CHANNEL_SGB, sizeof(channel));
	printf("iRet=[%d]\n",iRet);

	if(memcmp(channel, CHANNEL_SGB, sizeof(channel) - 1 ) == 0)
	{
		printf("memcmp's answer is 0!\n");
	}else{
		printf("memcmp's answer not equal 0!\n");
	}




	return 0;
}
