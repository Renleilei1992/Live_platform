/*

偏特化 类模板

*/

#ifndef _PAIR_H
#define _PAIR_H
#include <iostream>

using namespace std;

template <typename T1,typename T2>

class Pair
{
private:
	T1 first;
	T2 second;
public:
	Pair();					//声明未特化的构造函数
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair()		//定义未特化的构造函数
{
	cout<<"Pair<T1, T2>::Pair()"<<endl;
}

template <typename T2>	//偏特化该类 第一个类型为char
class Pair<char, T2>
{
public:
	Pair();				//声明偏特化后的构造函数
};

template <typename T2>
Pair<char, T2>::Pair()	//定义偏特化后的构造函数
{
	cout<<"Pair<char, T2>::Pair()"<<endl;
}

#endif
