//
// Challenge name: Problem 160
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=160
// Compile       : g++ -Wall -g -o p160 p160.cpp
// Run           : ./p160
//

#include <stdio.h>
#define INT unsigned long long int


INT last5digits(INT n) {
    INT prod = 1;
    for(INT i=1;i<=n;++i) {
        // compute the factorial
        prod *= i;
        // remove all trailing zeros
        while((prod % 10) == 0) {
            prod /= 10;
        }
        // take only the last 5 digits
        prod %= 100000;
    }
    return prod;
}

INT last5digits_improved(INT n) {
    INT digits = 100000ULL;
    INT prod = 1;
    INT pows = n / digits;
    // assumption: 'n' is evenly divisible by 'digits'!
    for(INT i=1;i<=digits;++i) {
        for(INT j=1;j<=pows;++j) {
            prod *= i;
            while(prod % 10 == 0) {
                prod /= 10;
            }
            prod %= digits;
        }
    }
    return prod;
}

int main(int argc, char** argv) {
    INT num = 1000000000000ULL;
    num = 10000000ULL;
    printf("f(%llu) = %llu\n", num, last5digits(num));
    printf("f(%llu) = %llu\n", num, last5digits_improved(num));
    return 0;
}
