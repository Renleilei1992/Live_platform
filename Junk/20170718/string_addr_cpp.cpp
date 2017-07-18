#include <iostream>
#include <cstring>

using namespace std;

void func_addr(char ptr[],int len);

int main(int argc, char **argv)
{
	char p[6] = "hello";
	cout << p[0] << endl;
	cout << static_cast<const void *>(&p[0]) << endl;
	func_addr(p, strlen(p));

	return 0;
}

void func_addr(char ptr[],int len)
{
	int i = 0;
	for (i = 0; i < len; ++i) {
		cout << "p[" << i << "]: " << ptr[i] << endl;
		cout << "addr: " << "p[" << i << "]" << static_cast<const void *>(&ptr[i]) << endl;		//强制转换类型为void*型指针，并将其地址打印出来
	}
}
