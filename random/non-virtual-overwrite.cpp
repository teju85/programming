// Example of overwriting a non-virtual member function.
//   All function calls will resolved at compile time.
//   Even if you go for a dynamic_cast, it will not help
//   as the function to be called would have already been
//   resolved at compile-time, based on the type of the
//   object calling this function!
#include <iostream>
using namespace std;

class A {
public:
    void f0() { cout << "Inside A\n"; }
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
