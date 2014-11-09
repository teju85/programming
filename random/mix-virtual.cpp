// Example of overwriting a virtual member function
// and then overwriting this overwritten function!
//   Once a function is declared as virtual in its base
//   class, it is virtual everywhere!
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

class C: public B {
public:
    void f0() { cout << "Inside C\n"; }
};


int main(int argc, char** argv) {
    A a;
    B b;
    C c;
    a.f0();
    b.f0();
    c.f0();
    A* cast = dynamic_cast<A*>(&b);
    cast->f0();
    B* castb = dynamic_cast<B*>(&c);
    castb->f0();
    return 0;
}
