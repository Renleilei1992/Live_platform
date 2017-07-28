
/* 通过strchr函数将一个字符串倒序输出，以空格分割的字符串 */

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc,char **argv)
{
	char str[100] = "Today is Monday!";
	char *p[10];
	int i = 0;

	cout<<"sizeof(str) = "<<sizeof(str)<<endl;
	cout<<"sizeof(p) = "<<sizeof(p)<<endl;

	for(;i<(sizeof(p)/sizeof(p[0]));++i){
		cout<<" i = "<<i<<endl;
		p[i] = (char *)malloc(sizeof(str));
	}


	for(i=0; i<(sizeof(p)/sizeof(p[0])); ++i){
		cout<<"sizeof(p["<<i<<"] = "<<sizeof(p[i])<<endl;
		free p[i];
	}

	return 0;
}
