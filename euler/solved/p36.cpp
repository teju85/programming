//
// Challenge name: Problem 36
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=36
// Compile       : g++ -Wall -g -o p36 p36.cpp
// Run           : ./p36
//

#include <stdio.h>
#include "include/integers.h"
#define LIMIT 1000000
#define INT int


bool is_palindrome_base2(INT a) {
    if(!(a & 0x1)) {
        return false;
    }
    INT i, j;
    // number of digits
    for(j=1;a>>j;++j);
    --j;
    // palindrome check
    for(i=0;i<j;++i,--j) {
        bool low = a & (1 << j);
        bool high = a & (1 << i);
        if(low != high) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    INT sum = 0;
    // even numbers can't be palindrome in base 2!
    for(INT num=1;num<=LIMIT;num+=2) {
        if(!is_palindrome<INT>(num)) {
            continue;
        }
        if(is_palindrome_base2(num)) {
            sum += num;
        }
    }
    printf("%d\n", sum);
    return 0;
}
