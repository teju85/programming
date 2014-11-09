//
// Challenge name: Problem 33
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=33
// Compile       : g++ -Wall -g -o p33 p33.cpp
// Run           : ./p33
//

#include <stdio.h>
#include "include/integers.h"
#define INT int

struct Rational {
    INT n;
    INT d;
};

void reduce(Rational& r) {
    INT g = gcd<INT>(r.n, r.d);
    r.n /= g;
    r.d /= g;
}

bool remove_common(Rational& c) {
    INT na = c.n / 10;
    INT nb = c.n % 10;
    INT da = c.d / 10;
    INT db = c.d % 10;
    if(na == da) {
        c.n = nb;
        c.d = db;
        return true;
    }
    else if(na == db) {
        c.n = nb;
        c.d = da;
        return true;
    }
    else if(nb == da) {
        c.n = na;
        c.d = db;
        return true;
    }
    else if(nb == db) {
        c.n = na;
        c.d = da;
        return true;
    }
    return false;
}

bool isUnorthodoxCancel(Rational temp) {
    Rational c = temp;
    if(!(c.n % 10) && !(c.d % 10)) {
        return false;
    }
    //printf("%d %d ", temp.n, temp.d);
    reduce(temp);
    bool status = remove_common(c);
    if(status && (c.n != 0) && (c.d != 0)) {
        reduce(c);
    }
    //printf("%d %d %d %d\n", c.n, c.d, temp.n, temp.d);
    if(!status) {
        return false;
    }
    return ((c.n == temp.n) && (c.d == temp.d));
}

int main(int argc, char** argv) {
    Rational prod = {1, 1};
    for(int n=10;n<100;++n) {
        for(int d=n+1;d<100;++d) {
            Rational temp = {n, d};
            if(isUnorthodoxCancel(temp)) {
                prod.n *= temp.n;
                prod.d *= temp.d;
                printf("%d %d %d %d\n", temp.n, temp.d, prod.n, prod.d);
            }
        }
    }
    reduce(prod);
    printf("Product: numerator=%d denominator=%d\n", prod.n, prod.d);
    return 0;
}
