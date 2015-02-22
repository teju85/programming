#include <stdio.h>
// compile with g++ -fno-rtti rtti.cpp

class Base {
public:
    Base() { printf("Constructor of base\n"); }
    virtual ~Base() { printf("Destructor of base\n"); }
    virtual void print() = 0;
};

class Child1: public Base {
public:
    Child1(): Base() { printf("Constructor of child1\n"); }
    ~Child1() { printf("Destructor of child1\n"); }
    void print() { printf("print from Child1\n"); }
};

class Child2: public Base {
public:
    Child2(): Base() { printf("Constructor of child2\n"); }
    ~Child2() { printf("Destructor of child2\n"); }
    void print() { printf("print from Child2\n"); }
};


int main(int argc, char** argv) {
    Base* obj1 = new Child1;
    obj1->print();
    delete obj1;
    Base* obj2 = new Child2;
    obj2->print();
    delete obj2;
    return 0;
}
