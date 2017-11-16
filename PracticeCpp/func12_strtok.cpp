
#include <iostream>
#include <string.h>
#include <cstdlib>

#define MAXLEN 1024

using namespace std;

int main(int argc,char **argv)
{
	int num = 0,i = 0;
	char str[MAXLEN]="Hello my Friend!";
    char *s;
    char *S[MAXLEN] = {};
    const char *delim = " ";
    s = strtok(str, delim);
    while(s != NULL){
//      cout<<s<<"      num="<<num<<endl;
        S[num]=(char *)malloc(sizeof(s));
        memset(S[num], 0x00, sizeof(s));
        memcpy(S[num],s,sizeof(s));
        s = strtok(NULL, delim);
        num++;
    }
//  cout<<"num= "<<num<<endl;
    for(i=num;i>0;i--){
        cout<<S[i-1]<<" ";
        free(S[i]);
    }
	free(S[0]);
	free(S[num+1]);
    cout<<endl;

    return 0;
}
