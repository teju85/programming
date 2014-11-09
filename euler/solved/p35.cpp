//
// Challenge name: Problem 35
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=35
// Compile       : g++ -Wall -g -o p35 p35.cpp
// Run           : ./p35
//

#include <stdio.h>
#include "include/seive.h"

#define LIMIT 1000000
#define DIGITS 9
#define INT  int

INT digits[DIGITS+1];

void initDigits() {
    for(INT i=0;i<=DIGITS;++i) {
        digits[i] = 0;
    }
}

INT getDigits(INT num) {
    INT i;
    for(i=0;num;++i,num/=10) {
        digits[i] = num % 10;
    }
    return i;
}

INT getInt(INT len) {
    INT num = 0;
    for(INT i=0,j=1;i<len;++i,j*=10) {
        num += (digits[i] * j);
    }
    return num;
}

void rotateRight(INT len) {
    INT d = digits[len-1];
    for(INT i=len-2;i>=0;--i) {
        digits[i+1] = digits[i];
    }
    digits[0] = d;
}

int main(int argc, char** argv) {
    eratos se(LIMIT);
    se.generate_seive();
    INT sum = 4;
    for(INT i=11;i<=LIMIT;i+=2) {
        if(!se.is_prime(i)) {
            continue;
        }
        initDigits();
        INT nd = getDigits(i);
        INT j;
        for(j=1;j<nd;++j) {
            rotateRight(nd);
            INT t = getInt(nd);
            if(!se.is_prime(t)) {
                break;
            }
        }
        if(j >= nd) {
            //printf("%d\n", i);
            ++sum;
        }
    }
    printf("num=%d\n", sum);
    return 0;
}
