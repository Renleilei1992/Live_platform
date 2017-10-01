
/* 熟悉string的用法  */


#include <string>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int main(int argc,char **argv)
{

	string str = "hello c++";

	cout<<str[1]<<endl;
	cout<<str.size()<<endl;

	return 0;

}
