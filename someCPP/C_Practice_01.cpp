#include <iostream>
#include <cstring>

extern "C"
using namespace std;

int main(void)
{
	cout << "Hello C++!" << endl;
	string str = "hello!";
	string str1 = {};
	char *p = "Hello string?!";

	cout << sizeof(str) <<" "<< endl;			//Êä³ö 28
	cout << sizeof(str1) <<" "<< endl;			//Êä³ö 28
	cout << *p << " " << p << " " << &p << endl;

	if (p) {
		cout << "Pointer is 1(true)!" << endl;	//if(p) => if(1)
	}

	return 0;
}