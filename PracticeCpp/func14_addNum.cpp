

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc,char **argv)
{
	int i = 10;

	int j = 0;

	cout<<"Plz input the num: ";
	cin>>j;

	int ans = j/i;
	cout<<"Answer= ["<<ans<<"]"<<endl;
	ans = 11%1;
	cout<<"Answer= ["<<ans<<"]"<<endl;
	ans = -1078;
	cout<<"abs(ans)= ["<<abs(ans)<<"]"<<endl;

	return 0;
}
