#include "ClassA.h"
#include <iostream>
using namespace std;

int ClassA::static_public_num = 7;
int ClassA::static_protected_num = 8;
int ClassA::static_private_num = 9;

void ClassA::print_num(){
    cout<<"IN FUNC: ClassA::print_num"<<endl;
    cout<<"ClassA::static_public_num "<<ClassA::static_public_num<<endl;
    cout<<"ClassA::static_protected_num "<<ClassA::static_protected_num<<endl;
    cout<<"ClassA::static_private_num "<<ClassA::static_private_num<<endl;
}