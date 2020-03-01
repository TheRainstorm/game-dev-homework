#include "String.h"

#include <iostream>
#include<cstdbool>
using namespace std;

int main() {
	String myStr1("hello world1");
	cout << "myStr1: " << endl;
	cout << myStr1.get() << endl;

	String myStr2;
	myStr2.set("hello world2");
	cout << "myStr2: " << endl;
	cout << myStr2.get() << endl;

	String myStr3(myStr1);
	cout << "myStr3: " << endl;
	cout << myStr3.get() << endl;
	myStr1.set("hello world1-change");	//²âÊÔÊÇ·ñ·ÇÇ³¿½±´
	cout << myStr3.get() << endl;

	String myStr4 = myStr3 = myStr2;
	cout << "myStr4: " << endl;
	myStr2.set("hello world2-change");
	cout << myStr3.get() << endl;
	cout << myStr4.get() << endl;

	String myStr5 = String("hello ") + String("world5");
	cout << "myStr5: " << endl;
	cout << myStr5.get() << endl;

	cout << "myst5 == myStr3: " << (myStr5 == myStr3) << endl;
	cout << "myst5 > myStr3: " << (myStr5 > myStr3) << endl;
	cout << "myst3 >= myStr5: " << (myStr3 >= myStr5) << endl;


	String myStr6 = "hello world6";
	cout << myStr6.search('w') << endl;
	cout << myStr6[myStr6.search('w')] << endl;
	cout << myStr6.search("world") << endl;

	return 0;
}