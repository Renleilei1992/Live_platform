#include <stdio.h>

int main(int argc,char* argv[])
{
	for(int i = 0; ; i++){
		if(i > 5){
			break;
		}
		printf("[i]=%d\n",i);
	}

	return 0;
}
