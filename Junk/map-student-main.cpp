#include <iostream>
#include "student.h"
#include <map>

using namespace std;

typedef bool (*func_t)(const Student&,const Student&);

bool stuCmp(const Student& s1,const Student& s2)
{
	return s1.getId() < s2.getId();
}

int main(int argc,char **argv)
{

	map<Student,double,func_t> stus(stuCmp);//学生(键)，成绩(值)
	map<Student,double>::iterator it;
	Student stu("Tom",1);
	Student stu1("Mike",2);

	pair<Student,double> p(stu,80);	//传入成绩80,下一步改为90
	pair<Student,double> p1(stu1,59);
	stus[stu] = 90;	//如果map中没有stu,则会创建这个键,返回键对应值的引用
	stus[stu1];		//查询一个不存在的键,会创建这个键，但是值为0

	stus.insert(p);		//学生无法比较大小,需要重载运算符或定义比较方法

	for(it = stus.begin(); it != stus.end(); it++)	//遍历寻找
	{
		const Student& stu = it -> first;
		double score = it -> second;
		stu.introduce();
		cout<<"score: "<<score<<endl;
	}

	return 0;
}
