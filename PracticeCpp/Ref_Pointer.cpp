#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	int ival = 42;
	int *p = &ival;				//�˴���&����Ϊȡ��ַ������ַͬʱ��ֵ��p��
	cout << "ival = " << ival << "  *p = " << *p << "  p = " << p << endl;			//42, 42, 0058FCF8
	int *p2 = p;					//�˴��ǽ�p��ֵ��ֵ��p2������p��p2��Ϊ��ַ�������൱�����Ǿ�ָ��ͬһ���ַ
	cout << "*p2 = " << *p2 << "   p2 = " << p2 << endl;									//42, 0058FCF8
	int &r1 = ival;
	int *p3 = nullptr;
	p3 = &r1;
	int &r2 = *p;
	cout << "r1 = " << r1 << "  &r1=" << &r1 << endl;
	cout << "*p3 = " << *p3 << "  p3 = " << p3 << "  r2 = " << r2 << "  &r2 = " << &r2 << endl;

	int *p1 = nullptr;			//��ָ��p1�ÿգ��ȼ���int *p1 = 0; (��p1��ʼ��Ϊ���泣��0)   �˷������� NULL��
	int *p4 = NULL;			//�ȼ���int *p2 = nullptr, int *p2 = 0; (��Ҫ���� cstdlib��)

	string str = "Hello!";
	p1 =(int*) &str;				//ͨ��ǿ��ת�����ͺ��ָ���ַ����ͬ�ģ�����ֵȴ��ͬ��ԭ�е�ֵ
	string *p5 = nullptr;
	p5 = &str;					//��ͬ���͵�ָ�룬��ַ��ͬ��ֵҲ��ͬ����ӹ���ɣ����ʹ��void��ָ�룬ֵ����ͬ��
	cout << str << "  " << &str << "  " << *p1 << "  " << p1 << "  p5 = " << p5 << "  *p5 = " << *p5 << endl;


	/*
	string str = "hello!";		//����if���ַ������Ƿ����á��˲�����linux C�����б�������ͨ��������C++�������޷�ͨ�����﷨
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
//	int &refval = ival;											//refvalָ�����ival����ival��ֵ����ʵ��ival����һ�����֣�������
//	cout << "ival = " << ival << endl;				
//	cout << "refval = " << refval << endl;
//	/*int &refval2;*/											//����䲻�Ϸ������ñ���Ҫ��ʼ��
//	refval = 2;
//	int ii = refval;												//��refval��ֵ��ii
//	int &refval3 = refval;									//�������� refval3,�󶨵�refval���󶨵Ķ����ϣ��˴����ǰ󶨵�ival��
//	int i = refval;													//�﷨��ȷ��i����ʼ��Ϊival��ֵ��
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
//	r2 = 3.14159;						//�Ϸ����˴�r2��i2�ı�������r2��ֵ���Ǹ�����i2��ֵ
//	r2 = r1;									//�Ϸ�����r1��ֵ��ֵ��r2,
//	//i1 = r2;									//�����棬��ʧ���ȣ��ᱻ��ʽת������˫���ȵ�ֵ��ֵ��������  !!!!!
//	//r1 = i2;									//�����棬��ʧ���ȣ�ͬ��  !!!!!!!!!
//	return 0;
//}