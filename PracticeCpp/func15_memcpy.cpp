/*

测试一个 memcpy 溢出的错误

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int main(int argc,char **argv)
{
	char str[MAX_LEN] = "Hello Memcpy!!!!";
	char ans[10 + 1];

	cout<<"sizeof(str)= ["<<sizeof(str)<<"]"<<endl; 	//1024
	cout<<"sizeof(ans)= ["<<sizeof(ans)<<"]"<<endl;		//11
	memset(ans, 0x00, sizeof(ans));						//初始化了一段11大小的空间
//	memcpy(ans, str, sizeof(str));						//向11大小的空间中拷贝了1024长度的数据，实际是溢出了
	/* 正确写法 */
	memset(ans, 0x00, sizeof(ans));
	memcpy(ans, str, sizeof(ans)-1);

	cout<<ans<<endl;
	cout<<str<<endl;

	return 0;
}
