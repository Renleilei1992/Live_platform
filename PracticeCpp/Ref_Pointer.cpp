#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	int ival = 42;
	int *p = &ival;				//此处的&符号为取地址符，地址同时赋值给p；
	cout << "ival = " << ival << "  *p = " << *p << "  p = " << p << endl;			//42, 42, 0058FCF8
	int *p2 = p;					//此处是将p的值赋值给p2，由于p和p2均为地址，所以相当于他们均指向同一块地址
	cout << "*p2 = " << *p2 << "   p2 = " << p2 << endl;									//42, 0058FCF8
	int &r1 = ival;
	int *p3 = nullptr;
	p3 = &r1;
	int &r2 = *p;
	cout << "r1 = " << r1 << "  &r1=" << &r1 << endl;
	cout << "*p3 = " << *p3 << "  p3 = " << p3 << "  r2 = " << r2 << "  &r2 = " << &r2 << endl;

	int *p1 = nullptr;			//将指针p1置空，等价于int *p1 = 0; (将p1初始化为字面常量0)   此方法优于 NULL！
	int *p4 = NULL;			//等价于int *p2 = nullptr, int *p2 = 0; (需要包含 cstdlib库)

	string str = "Hello!";
	p1 =(int*) &str;				//通过强制转换类型后的指针地址是相同的，但是值却不同于原有的值
	string *p5 = nullptr;
	p5 = &str;					//相同类型的指针，地址相同且值也相同（毋庸置疑，如果使用void型指针，值不相同）
	cout << str << "  " << &str << "  " << *p1 << "  " << p1 << "  p5 = " << p5 << "  *p5 = " << *p5 << endl;


	/*
	string str = "hello!";		//测试if（字符串）是否有用。此测试在linux C环境中编译器可通过，但是C++编译器无法通过此语法
	string str1 = NULL;
	if (str1) {
		cout << str << endl;
	}
	*/

	return 0;
}

//int main(int argc, char **argv)
//{
//	int ival = 1024;
//	int &refval = ival;											//refval指向的是ival，绑定ival的值（其实是ival的另一个名字，别名）
//	cout << "ival = " << ival << endl;				
//	cout << "refval = " << refval << endl;
//	/*int &refval2;*/											//此语句不合法，引用必须要初始化
//	refval = 2;
//	int ii = refval;												//将refval赋值给ii
//	int &refval3 = refval;									//定义引用 refval3,绑定到refval所绑定的对象上，此处即是绑定到ival上
//	int i = refval;													//语法正确，i被初始化为ival的值；
//	cout << "refval = " << refval << endl;
//	cout << "refval3 = " << refval3 << endl;
//	cout << "i = " << i << endl;
//	ival = 2048;
//	cout << "After change ival, The refval = " << refval << endl;							//2048
//	cout << "After change ival, The refval3 = " << refval3 << endl;						//2048
//	refval = 4096;
//	cout << "After change refval, The ival = " << ival << endl;								//4096
//	cout << "After change refval, The refval3 = " << refval3 << endl;					//4096
//
//	int i1 = 5, &r1 = i1;
//	double i2 = 0, &r2 = i2;
//	r2 = 3.14159;						//合法，此处r2是i2的别名，向r2赋值即是更改了i2的值
//	r2 = r1;									//合法，将r1的值赋值给r2,
//	//i1 = r2;									//报警告，丢失精度，会被隐式转换，把双精度的值赋值给单精度  !!!!!
//	//r1 = i2;									//报警告，丢失精度，同上  !!!!!!!!!
//	return 0;
//}