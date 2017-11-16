#include <iostream>
#include <cstring>
#include <cassert>

extern "C"
using namespace std;

long fact(int n);											//求n！ 的函数
void TOH(int n, char a, char b, char c);		//汉诺塔函数

int main(void)
{
//	cout << fact(10) << endl;
	TOH(6, 'A', ' B', ' C');
	system("pause");
	return 0;
}

void TOH(int n, char a, char b, char c)
{
	if (n == 0) return;
	if (n == 1) {
		cout << a << "->" << c << endl;
	}
	if (n > 1) {
		TOH(n - 1, a, c, b);
		cout << a << "->" << c << endl;
		TOH(n - 1, b, a, c);
	}
}

long fact(int n)	//compute n!
{
	//To fit n!    in a long variable require n<=12
	assert((n > 0) && (n <= 12), "Input out of range!");
	if (n <= 1)return 1;
	return n*fact(n - 1);
}
//int main(int argc, char **argv)
//{
//	char str_testForKOAL[] = "0123456789\0abcdef";
//	int len_1 = sizeof(str_testForKOAL);
//	int len_2 = strlen(str_testForKOAL);
//	int len_3 = strlen(&str_testForKOAL[11]);
//
//	cout << "len_1 = " << len_1 << endl;
//	cout << "len_2 = " << len_2 << endl;
//	cout << "len_3 = " << len_3 << endl;
//	return 0;
//}