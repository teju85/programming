//
// Challenge name: Problem 16
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=16
// Compile       : g++ -Wall -g -o p16 p16.cpp
// Run           : ./p16
//

#include <stdio.h>
#include "include/bigint.h"

int main(int argc, char** argv) {
    BigInt big((uint32)1);
    big <<= 1000;
    printf("%u\n", big.digit_sum());
    //printf("%s\n", big.get_string().c_str());
    return 0;
}
