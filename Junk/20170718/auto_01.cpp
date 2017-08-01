#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	unsigned scores[11] = {};
	unsigned grade;
	int count = 0;

	while (cin >> grade){
		if (grade <= 100 & count<10) {
			++scores[grade / 10];
			++count;
		}else{
			break;
		}
	}

	for (auto i : scores) 
		cout << i << " ";
	cout << endl;
	return 0;
}
