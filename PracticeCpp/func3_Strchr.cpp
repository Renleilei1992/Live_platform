
/* 通过strchr函数将一个字符串倒序输出，以空格分割的字符串 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

int main(int argc,char **argv)
{
	char str[100] = "Today is Monday!";
	char *p[10];
	int i = 0;

	cout<<"sizeof(str) = "<<sizeof(str)<<endl;
	cout<<"sizeof(p) = "<<sizeof(p)<<endl;

	for(i=0; i<(sizeof(p)/sizeof(p[0])); ++i){
		p[i] = (char *)malloc(sizeof(str));
		memset(p[i], 0x00, sizeof(p[i]));
//		strcpy(p[i],static_cast<char *>(&str[i]));
		strcpy(p[i],&str[i]);
//		strcpy(p[i],"h");
		cout<<" i= "<<i<<"  p["<<i<<"]="<<p[i]<<"  str[i]="<<str[i]<<endl;
	}


	for(i=0; i<(sizeof(p)/sizeof(p[0]))+1; ++i){
		cout<<"sizeof(p["<<i<<"] = "<<sizeof(p[i])<<endl;
		free(p[i]);
//		delete p[i];
	}

	return 0;
}
