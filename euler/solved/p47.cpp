//
// Challenge name: Problem 47
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=47
// Compile       : g++ -Wall -g -o p47 p47.cpp
// Run           : ./p47
//

#include <stdio.h>
#include <map>
#include "include/seive.h"
#define CONSEC 4
#define INT long long int
#define LIMIT 1000000

using namespace std;
typedef map<INT, bool> primeFacs;


bool workOnPrimeFactor(primeFacs& factors, INT& num, INT mult) {
    INT fac = 1;
    while((num > 1) && !(num % mult)) {
        num /= mult;
        fac *= mult;
    }
    if(factors.find(fac) != factors.end()) {
        return false;
    }
    else {
        factors[fac] = true;
        //printf("num=%lld mult=%lld fac=%lld\n", num, mult, fac);
        return true;
    }
}

bool findDistinctPrimes(primeFacs& factors, INT num, const eratos& se) {
    if(num <= 1) {
        return true;
    }
    INT fac;
    INT numFac = 0;
    for(fac=2;num>1;++fac) {
        if(!se.is_prime(fac)) {
            continue;
        }
        if(num % fac) {
            continue;
        }
        if(!workOnPrimeFactor(factors, num, fac)) {
            return false;
        }
        ++numFac;
    }
    if(numFac != CONSEC) {
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    eratos se(LIMIT);
    se.generate_seive();
    INT limit = LIMIT - CONSEC;
    for(INT i=10;i<limit;++i) {
        INT j;
        primeFacs factors;
        for(j=0;j<CONSEC;++j) {
            if(se.is_prime(i+j)) {
                i += j;
                break;
            }
            if(!findDistinctPrimes(factors, i+j, se)) {
                break;
            }
        }
        //printf("%lld\n", i);
        if(j >= CONSEC) {
            printf("Start=%lld\n", i);
            break;
        }
    }
    return 0;
}
