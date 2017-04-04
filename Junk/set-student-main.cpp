#include <iostream>
#include "student.h"
#include <set>

using namespace std;

bool stuCmp(const Student& s1,const Student& s2);

typedef bool (*fun_t)(const Student& s1,const Student& s2);

bool stuCmp(const Student& s1,const Student& s2)
{
	return s1.getId() < s2.getId();
}
	
int main(int argc,char** argv)
{
	set<Student,fun_t> stus(stuCmp);
	set<Student>::iterator it;
	
	Student stu("Tom",1);
	Student stu1("Mike",2);
	Student stu2("Peter",3);
	stus.insert(stu);
	stus.insert(stu1);
	stus.insert(stu2);

	stus.erase(stus.begin());		//删除第一个元素的迭代器

	for(it = stus.begin(); it != stus.end(); it++)
	{
		it -> introduce();
	}

	set<Student>::iterator ret = stus.find(stu);//查询

	if(ret == stus.end())
	{
		cout<<"no such student!"<<endl;
	}else
	{
		ret -> introduce();
	}

	return 0;
}
