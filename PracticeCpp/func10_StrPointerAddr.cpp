#include <iostream>
using namespace std;

int main(int argc,char **argv)
{
	const void *myVoidPointer = "131420";
    const char *myStr = "Hello Cpp!";
     
    // stdout the pointer
	cout << "[pointer]: "<< myVoidPointer << endl;
    cout << "[string]: " << myStr << endl;
                
    // stdout the string's pointer's address
    cout << "[string's address]:　" << static_cast<const void *>(myStr) << endl;
 
    return 0;
}
