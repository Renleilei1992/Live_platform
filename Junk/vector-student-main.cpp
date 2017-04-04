/*

   迭代器

*/


#include <iostream>
#include <vector>
#include "student.h"

using namespace std;

void test1()	//迭代器指向数组
{
	vector<int> arr;
	vector<int>::iterator it;
	int i = 0;
	for(i = 0; i<9;i++)
	{
		arr.push_back(i);
	}
	for(it = arr.begin(); it != arr.end(); it++)	//迭代器
	{
		cout<<*it<<endl;
	}
}

void test2()	//迭代器指向数据类型
{
	vector<Student> arr;
	vector<Student>::iterator it;
	int i = 0;
	for(i=0; i<10; i++)
	{
		Student stu("Tom",i);
		arr.push_back(stu);
	}
	for(it = arr.begin(); it != arr.end(); it++)	//迭代器
	{
//		it -> introduce();		//it 作为一个指针可以调用函数
		const Student& rStu = *it;	//取值it(指针)，两种方法都可以
		rStu.introduce();
	}
}

void test3()
{
	vector<int> arr;
	vector<int>::iterator it;
	int i = 0;
	for(i=0; i<10; i++)
	{
		arr.push_back(i);
	}
	it = arr.end()-1;	//指向最后一个元素
	cout<<"*it: "<<*it<<endl;

	arr.pop_back();		//删除最后一个元素
	cout<<"*it: "<<*it<<endl;	//迭代器已经失效,动作很危险,不会报错
}

int main(int argc,char **argv)
{
//	test1();
//	test2();
	test3();
	return 0;
}
