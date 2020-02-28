#ifndef CLASSA_H
#define CLASSA_H

class ClassA{
public:
    static int static_public_num;
protected:
    static int static_protected_num;
private:
    static int static_private_num;

public:
    static void print_num();
};

#endif