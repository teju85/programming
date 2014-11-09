//
// Challenge name: Problem 48
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=48
// Compile       : g++ -Wall -g -o p48 p48.cpp
// Run           : ./p48
//
#include <stdio.h>
#define INT unsigned long long int
#define MAX 1000ULL
#define NUM 10000000000ULL


int main(int argc, char** argv) {
    INT sum = 1ULL;
    for(INT num=2ULL;num<=MAX;++num) {
        INT pow  = 1ULL;
        for(INT i=1ULL;i<=num;++i) {
            pow = (pow * num) % NUM;
        }
        /*
        INT popo2 = num;
        INT pow = (num & 1ULL)? num : 1ULL;
        // right-to-left-binary-exponentiation
        for(INT po2=2ULL;po2<=num;po2<<=1ULL) {
            popo2 = (popo2 * popo2) % NUM;
            if(po2 & num) {
                pow = (pow * popo2) % NUM;
            }
        }
        */
        sum = (sum + pow) % NUM;
    }
    printf("%llu\n", sum);
    return 0;
}
