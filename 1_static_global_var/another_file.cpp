#include <iostream>
using namespace std;

int global_outer_num = 4;
static int static_global_outer_num = 5;

void print_num_in_other() {
	cout << "In func: print_num_in_other" << endl;
	cout << "global_outer_num: " << global_outer_num << endl;
	cout << "static_global_outer_num: " << static_global_outer_num << endl;
}