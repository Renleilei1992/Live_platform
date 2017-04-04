#include "pair.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	Pair<int,char> p1;	//调用非偏特化的类模板
	Pair<char,int> p2;	//调用偏特化后的类模板

	return 0;
}
