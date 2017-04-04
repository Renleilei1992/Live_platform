/*

 vector 的使用

*/

#ifndef _STUDENT_H
#define _STUDENT_H

#include <string>

using namespace std;

class Student
{
private:
	int id;
	string name;
public:
	Student(const string& name,int id);
	int getId()const{return id;}

	void introduce()const;
};



#endif
