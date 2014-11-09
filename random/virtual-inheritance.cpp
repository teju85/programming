// Example of solving the diamond problem using virtual inheritance.
#include <iostream>
using namespace std;

class A {
public:
    virtual void f0() { cout << "Inside A\n"; }
};

class B: virtual public A {
public:
    void f1() { cout << "Inside B\n"; }
    void f0() { cout << "Inside B\n"; }
};

class C: virtual public A {
public:
    void f2() { cout << "Inside C\n"; }
};

class D: public B, public C {
};


int main(int argc, char** argv) {
    D d;
    d.f0();
    return 0;
}
