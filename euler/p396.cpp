//
// Challenge name: Problem 396
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=396
// Compile       : g++ -Wall -g -o p396 p396.cpp
// Run           : ./p396
//

#include <stdio.h>

#define INT unsigned long long int
#define MAX_DIGITS 7

INT digits[MAX_DIGITS];
int numDigits = 0;

void convertToBase2(int n) {
    for(int i=0;i<MAX_DIGITS;++i) {
        digits[i] = 0;
    }
    numDigits = 0;
    while(n) {
        digits[numDigits] = (INT) (n & 0x1);
        n >>= 1;
        ++numDigits;
    }
}

void subtractOnBaseN(INT b) {
    digits[0] = b - 1;
    for(int i=1;i<numDigits;++i) {
        if(digits[i] > 0) {
            --digits[i];
            break;
        }
        else if(digits[i] == 0) {
            digits[i] = b - 1;
        }
    }
    if(digits[numDigits-1] == 0) {
        --numDigits;
    }
}

void printNumber() {
    for(int i=MAX_DIGITS-1;i>=0;--i) {
        printf("%llu ", digits[i]);
    }
    printf(" numDigits=%d\n", numDigits);
}

INT weakGoodsteinSequenceLength(int n) {
    if(n <= 0) {
        return 0;
    }
    if(n == 1) {
        return 1;
    }
    INT i = 1;
    convertToBase2(n);
    while(numDigits > 1) {
        i += (digits[0] + 1);
        subtractOnBaseN(i+1);
    }
    return ((i << 1) - 1);
}

INT sumOfLengths(int n) {
    INT sum = 0;
    for(int i=1;i<n;++i) {
        sum += weakGoodsteinSequenceLength(i);
    }
    return sum;
}

int main(int argc, char** argv) {
    printf("%d %llu\n", 10, sumOfLengths(10));
    return 0;
}
