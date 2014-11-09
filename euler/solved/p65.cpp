//
// Challenge name: Problem 65
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=65
// Compile       : g++ -Wall -g -o p65 p65.cpp
// Run           : ./p65
//

#include <stdio.h>
#include "include/integers.h"
#include "include/bigint.h"
#define INT BigInt


struct Rational {
    INT n;
    INT d;
};

void add(Rational& rat, const Rational& right) {
    INT d = lcm<INT>(rat.d, right.d);
    INT n = ((d / rat.d) * rat.n) + ((d / right.d) * right.n);
    rat.n = n;
    rat.d = d;
}

void add(Rational& rat, uint32 num) {
    Rational right;
    right.n.set_uint32(num);
    right.d.set_uint32(1);
    add(rat, right);
}

void invert(Rational& rat) {
    swap<INT>(rat.n, rat.d);
}



uint32 denom_at(uint32 loc) {
    if(loc == 1) {
        return 2;
    }
    if(!(loc % 3)) {
        uint32 k = loc / 3;
        return (k << 1);
    }
    return 1;
}

void print_rational(const Rational& rat, bool dec=true) {
    printf("numerator=%s\ndenominator=%s\n",
           rat.n.get_string(dec).c_str(), rat.d.get_string(dec).c_str());
}


int main(int argc, char** argv) {
    Rational rat;
    rat.n.set_uint32(0);
    rat.d.set_uint32(1);
    int32 itr = 100;
    for(;itr>0;--itr) {
        add(rat, denom_at((uint32)itr));
        invert(rat);
        //printf("ITER=%d\n", itr);
        //print_rational(rat);
        //printf("\n");
    }
    invert(rat);   // needed as there's an extra inversion
    printf("FINAL...\n");
    print_rational(rat);
    printf("\n");
    printf("NUMERATOR-SUM=%u\n", rat.n.digit_sum());
    return 0;
}
