/*

������ּ��ʹ����������Ÿ������ֳ��ֵĴ������������ʹ��10����������������

*/

#include <iostream>
#include <cstdio>

extern "C"
using namespace std;

int main(void)
{
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;
	for (int i = 0; i < 10; ++i) {
		ndigit[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9') {
			++ndigit[c - '0'];
		}
		else if (c == '  ' || c == '\n' || c == '\t') {
			++nwhite;
		}
		else {
			++nother;
		}
	}

	cout << "digits = ";
	for (i = 0; i < 10; i++) {
		cout << ndigit[i];
	}
	cout << ", white space = " << nwhite << ", nother = " << nother << endl;

	return 0;
}