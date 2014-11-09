// Example of overwriting a virtual member function.
//   All function calls will resolved at run-time.
//   You can't use 'static_cast' here as that would
//   not make sense. Remember we are using RTTI here!?
#include <iostream>
using namespace std;

class A {
public:
    virtual void f0() { cout << "Inside A\n"; }
};

class B: public A {
public:
    void f0() { cout << "Inside B\n"; }
};


int main(int argc, char** argv) {
    A a;
    B b;
    a.f0();
    b.f0();
    A* cast = dynamic_cast<A*>(&b);
    cast->f0();
    return 0;
}
