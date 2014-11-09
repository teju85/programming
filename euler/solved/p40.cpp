//
// Challenge name: Problem 40
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=40
// Compile       : g++ -Wall -g -o p40 p40.cpp
// Run           : ./p40
//

#include <stdio.h>
#define INT long long int

INT pow10(INT exp) {
    INT p = 1;
    while(exp > 0) {
        p *= 10;
        --exp;
    }
    return p;
}

INT totalDigits(INT digits) {
    return (digits * 9 * pow10(digits - 1));
}

INT findNumDigits(INT pos) {
    INT total = 0;
    INT d;
    for(d=1;total<pos;++d) {
        total += totalDigits(d);
    }
    --d;
    return d;
}

INT getIthDigit(INT num, INT i) {
    INT d = 0;
    for(;i>=0;--i) {
        d = num % 10;
        num /= 10;
    }
    return d;
}

INT digitAt(INT pos) {
    INT d = findNumDigits(pos);
    INT till = 0;
    for(INT i=1;i<d;++i) {
        till += totalDigits(i);
    }
    INT del = pos - till - 1;
    INT loc = d - (del % d) - 1;
    INT val = (del / d) + pow10(d-1);
    INT digit = getIthDigit(val, loc);
    printf("d=%lld del=%lld val=%lld loc=%lld digit=%lld\n",
           d, del, val, loc, digit);
    return digit;
}

int main(int argc, char** argv) {
    INT prod = 1;
    for(INT i=1;i<=1000000;i*=10) {
        prod *= digitAt(i);
    }
    printf("prod=%lld\n", prod);
    return 0;
}
