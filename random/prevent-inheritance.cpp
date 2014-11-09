#include <iostream>

class Usable;

class Usable_lock {
    friend class Usable;
private:
    Usable_lock() {}
    Usable_lock(const Usable_lock& a) {}
};

class Usable: public virtual Usable_lock {
public:
    Usable(const char* s) {}
    ~Usable() {}
    void print() { std::cout << "From Usable!\n"; }
};

class Derived: public Usable {
public:
    Derived(const char* s) :Usable(s) {}
};

int main(int argc, char** argv) {
    Derived a("fsdfds");    // --> This will cause compilation error!
    Usable u("fsdfds");
    u.print();
    return 0;
}
