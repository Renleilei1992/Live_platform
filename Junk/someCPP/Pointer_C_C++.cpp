#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main(void)
{
	string str = "Hello World!";
	char *str1 = "Hello World!";
	string *str_new = nullptr;
	str_new = &str;

	string a = "Hello C/C++!";
	string b = "Hello C/C++!";
	string *aa = nullptr;
	string *bb = nullptr;
	aa = &a;
	bb = &b;

	cout << "string str's size ="<<sizeof(str) <<" str_new="<<*str_new<< endl;	//28 	//32(因为此Linux系统为64位,28是因为VS社区版本只有32位)
	cout << "char *str1's size =" << sizeof(*str1) <<" *str1="<<*str1<< endl;	//1
	cout << "char str1's size =" << sizeof(str1) << endl;						//4		//8

	if (aa == bb) {
		cout << "aa == bb" << endl;
	}
	else {
		cout << "aa != bb" << endl;		// it's not equal!
		cout << aa << " "<<a<<endl;
		cout << bb << " "<<b<<endl;
	}
	if (a == b) {
		cout << "a == b" << endl;		// it's equal!
	}
	else {
		cout << "a != b" << endl;
	}

	char *c = "hello c!";		//常量池 常量区
	char *d = "hello c!";
	if (c == d) {
		cout << "c == d (address same!)" << endl;		// it's equal!
	}
	else {
		cout << " c != d (address different!)" << endl;
	}
	return 0;
}




//#include <stdio.h>
//#include <stdlib.h>
//
//extern "C"
//
//int main(void)
//{
//	char *str = "Hello Pointer!";
//	char str1;
//
//	int size_pointer = sizeof(*str);
//	int size_pointer1 = sizeof(str1);
//	printf("size_pointer = %d\n", size_pointer);
//	printf("str = %d\n", str);
//	printf("size_pointer1 = %d\n", size_pointer1);
//
//	return 0;
//}
