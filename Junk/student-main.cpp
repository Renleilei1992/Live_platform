#include <iostream>
#include "student.h"
#include <vector>
#include <algorithm>

using namespace std;

bool stuCmp(const Student& stu1,const Student& stu2)
{
	return stu1.getId() > stu2.getId();
}

void test()
{
	vector<Student> stus;
	int i = 0;
	for(i=0; i<10; i++)
	{
		Student stu("Tom",i);
		stus.push_back(stu);
	}
	sort(stus.begin(),stus.end(),stuCmp);
	for(i=0; i<10;i++)
	{
		stus[i].introduce();
	}
}

int main(int argc,char **argv)
{
	int i = 0;
	vector<int> arr;	//vector是一个类模板
	arr.push_back(5);
	arr.push_back(4);
	arr.push_back(6);

/*	cout<<arr[1]<<endl;
	arr.pop_back();		//删除数组最后的一个元素
	arr.push_back(7);	//添加一个元素7进入数组
	cout<<arr[2]<<endl;*/

	arr.push_back(7);
	sort(arr.begin(),arr.end());

	for(i=0; i<4; i++)
	{
		cout<<arr[i]<<endl;
	}
	
	test();
	return 0;
}
