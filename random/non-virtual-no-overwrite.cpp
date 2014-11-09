// Example of not overwriting a non-virtual member function.
// However, trying to change its interface.
//   
#include <iostream>
using namespace std;

class A {
public:
    void f0() { cout << "Inside A\n"; }
};

class B: public A {
public:
    using A::f0;
    void f0(int a) { cout << "Inside B " << a << "\n"; }
};


int main(int argc, char** argv) {
    A a;
    B b;
    a.f0();
    b.f0();
    b.f0(22);
    A* cast = dynamic_cast<A*>(&b);
    cast->f0();
    return 0;
}
