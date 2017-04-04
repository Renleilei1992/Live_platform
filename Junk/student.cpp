#include "student.h"
#include <iostream>

using namespace std;

Student::Student(const string& name,int id)
	:id(id),name(name)
{

}

void Student::introduce()const
{
	cout<<id<<":"<<name<<endl;
}
