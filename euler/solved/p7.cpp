//
// Challenge name: Problem 7
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=7
// Compile       : g++ -Wall -g -o p7 p7.cpp
// Run           : ./p7
//

#include <stdio.h>
#include "include/integers.h"

int main(int argc, char** argv) {
    int num = 10001;
    --num; // 2 is prime!
    int prime = 3;
    while(true) {
        if(is_prime(prime)) {
            if(num <= 1) {
                break;
            }
            --num;
        }
        prime += 2;
    }
    printf("%d\n", prime);
    return 0;
}
