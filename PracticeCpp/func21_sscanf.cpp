

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

extern "C"

int main(int argc,char **argv)
{
	char s[5000];
	char s1[5];
	char s2[50];
	char s3[50];
	char s4[50];
	
	memset(s, 0x00, sizeof(s));

	strncpy(s, "helloC|world|hey|Cplusplus:)11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111222222222222222222222222222222222222223333333333333333333333333333333333444444444444444444444444444444444444444666666666666666666666666666666666666", sizeof(s));

	sscanf(s, "%[^|]|%[^|]|%[^|]|%[^|]", s1, s2, s3, s4);

	cout<<"s = "<<s<<"  sizeof(s)= "<<sizeof(s)<<endl;
	cout<<"s1= "<<s1<<"  sizeof(s1)= "<<sizeof(s1)<<endl;
	cout<<"s2= "<<s2<<"  sizeof(s2)= "<<sizeof(s2)<<endl;
	cout<<"s3= "<<s3<<"  sizeof(s3)= "<<sizeof(s3)<<endl;
	cout<<"s4= "<<s4<<"  sizeof(s4)= "<<sizeof(s4)<<endl;

	return 0;
}
