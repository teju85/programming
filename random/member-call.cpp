#include <iostream>

class Temp {
public:
    Temp() {}
    ~Temp() {}
    void func1() { Temp::func2(); }
    void func2() { std::cout << "Inside func2" << std::endl; }
};

int main(int argc, char** argv) {
    Temp t;
    t.func1();
    return 0;
}
