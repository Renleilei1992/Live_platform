

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

extern "C"

#define PATH "~/shell/ftp.sh"


int main(int argc,char **argv)
{
	char a[16] = {0};
	char path[254 + 1];
	int i = 0;
	char sCmd[512 + 1];
	char s1[28];
	char s2[1];
	char s3[200];
	char s4[200];
	char s5[20];
	char s6[8];
	char s7[128];
	char s8[60];
	char s9[254];

	cout<<"sizeof(a[10])= "<<sizeof(a)<<endl;
	cout<<"strlen(a[10])= "<<strlen(a)<<endl;

	i = snprintf(a, 13, "%012d", 12345);			//i = [12]  a = [000000012345]
	cout<<"i = ["<<i<<"]  a = ["<<a<<"]"<<endl;
	i = snprintf(a, 9, "%012d", 12345);				//i = [12]  a = [00000001]
	cout<<"i = ["<<i<<"]  a = ["<<a<<"]"<<endl;

	/* int snprintf(char *str, size_t size, const char *format, ...);  */
	i = snprintf(path, sizeof(path), "%s/%s/%s/", "~/file/Recv/", "101", "20171010");

	cout<<"sizeof(path)= "<<sizeof(path)<<"  i = "<<i<<endl;
	cout<<"path: "<<path<<endl;
	cout<<"sizeof(i)= "<<sizeof(i)<<endl;
	cout<<"sizeof(PATH)= "<<sizeof(PATH)<<endl;

	/*测试溢出*/
	memset(sCmd, 0x00, sizeof(sCmd));
	memset(s1, 0x00, sizeof(s1));
	memset(s2, 0x00, sizeof(s2));
	memset(s3, 0x00, sizeof(s3));
	memset(s4, 0x00, sizeof(s4));
	memset(s5, 0x00, sizeof(s5));
	memset(s6, 0x00, sizeof(s6));
	memset(s7, 0x00, sizeof(s7));
	memset(s8, 0x00, sizeof(s8));
	memset(s9, 0x00, sizeof(s9));

	i = snprintf(sCmd, sizeof(sCmd), "%s %s %s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7, s8, s9);
	
	return 0;
}
