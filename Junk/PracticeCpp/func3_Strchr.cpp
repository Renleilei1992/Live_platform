
/* 通过strchr函数将一个字符串倒序输出，以空格分割的字符串 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>

#define MAXLEN 1024

using namespace std;

int main(int argc,char **argv)
{
	char str[100] = "Today is Monday!";
	char p[20] = {};
	int i = 0, j = 0;
	int count_space = 0;
	int len = strlen(str) - 1;
	int space_flag[] = {};
	
	cout<<"sizeof(str) = "<<sizeof(str)<<endl;
	cout<<"sizeof(p) = "<<sizeof(p)<<endl;
	cout<<"strlen(str) = "<<len<<endl;

	memset(p, 0x00, sizeof(p)-1);
	strcpy(p,str);
	for(i=0; i<(sizeof(p)/sizeof(p[0])); ++i){
//		p[i] = (char)malloc(sizeof(p[0]));
//		strcpy(p[i],static_cast<char *>(&str[i]));
//		strcpy(p[i],"h");
		if(p[i] == '\0')
			break;

		cout<<" i= "<<i<<"  p["<<i<<"]="<<p[i]<<"  str[i]="<<str[i]<<endl;

		if(p[i] == ' '){
			count_space++;
			space_flag[count_space-1]=i;
		}
	}

	cout<<"空格数量: "<<count_space<<endl;		//2
	for(i=count_space+1;i>0;i--){
		if((i-count_space) >= 0){
//			cout<<"空格位置: "<<space_flag[i-count_space]<<endl;
		}
		cout<<" ";
	}

	int num = 0;
	char *s;
	char *S[MAXLEN] = {};
	const char *delim = " ";
	s = strtok(str, delim);
	while(s != NULL){
		cout<<s<<"      num="<<num<<endl;
		S[num]=(char *)malloc(sizeof(s));
		memset(S[num], 0x00, sizeof(s));
		memcpy(S[num],s,sizeof(s));
		s = strtok(NULL, delim);
		num++;
	}
	cout<<"num= "<<num<<endl;
	for(i=num;i>0;i--){
		cout<<S[i-1]<<" ";
		free(S[i]);
	}
	cout<<endl;

	return 0;
}
