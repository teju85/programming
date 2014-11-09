//
// Challenge name: Problem 20
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=20
// Compile       : g++ -Wall -g -o p20 p20.cpp
// Run           : ./p20
//

#include <stdio.h>
#include "include/bigint.h"
#define INT unsigned long long int
#define LIMIT 0xffffffffULL

int main(int argc, char** argv) {
    INT num = 100;
    BigInt fact(1ULL);
    for(;num>0;--num) {
        fact *= num;
    }
    printf("%u\n", fact.digit_sum());
    //printf("%s\n", fact.get_string().c_str());
    return 0;
}
