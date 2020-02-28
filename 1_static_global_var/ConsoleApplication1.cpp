// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ClassA.h"
using namespace std;

extern int global_outer_num;
//int global_outer_num = 10; //Error	LNK2005	"int global_outer_num" (?global_outer_num@@3HA) already defined in 
extern int static_global_outer_num;
void print_num_in_other();

int global_num = 0;
static int static_global_num = 1;

void print_num(int cnt) {
	int auto_num = 2;
	static int static_auto_num = 3;

	cout << "IN FUNC: print_num, cnt: " << cnt << endl;
	cout << "auto_num: " << auto_num << endl;
	cout << "static_auto_num: " << static_auto_num << endl;

	auto_num++;
	static_auto_num++;

	cout << "global_num: " << global_num << endl;
	cout << "static_global_num: " << static_global_num << endl;
	global_num++;
	static_global_num++;
}

int main()
{
	{
		int block_auto_num = 10;
	}
	/*
	The difference in 作用域
	*/
	//全局变量可以在任何地方(同一文件)引用，局部变量只能在定义的函数内(或块内)引用
	cout << "global_num: " << global_num << endl;
	cout << "static_global_num: " << static_global_num << endl;
	// cout <<"auto_num"<<auto_num<<endl; //error
	// cout <<"static_auto_num"<<static_auto_num<<endl; //error
	// cout <<"block_auto_num"<< block_auto_num <<endl; //error

	//非静态的全局变量还可以通过extern跨文件引用，而静态的不能
	cout << "global_outer_num: " << global_outer_num << endl;
	// cout <<"static_outer_global_num: "<<static_outer_global_num<<endl; //error
	//非静态的全局变量通过该文件所在的函数是可以引用的
	print_num_in_other();

	//静态成员变量可以通过对象和类名来访问。
	ClassA obj1 = ClassA();
	cout<<obj1.static_public_num<<endl;
	cout<<ClassA::static_public_num<<endl;
	// cout<<ClassA::static_protected_num<<endl; //error
	//在类的函数内可以通过类名访问protected, private限制的static变量。
	ClassA::print_num();
	/*
	The difference in 生命周期
	*/
	//非静态局部变量在每次调用函数时，都会在栈中重新分配，函数调用结束时销毁。
	//静态局部变量在第一次定义时被存储在堆中，函数调用结束时不会销毁，因此可以保留值。
	print_num(0);
	print_num(1);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
