//
// Challenge name: Problem 4
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=4
// Compile       : g++ -Wall -g -o p4 p4.cpp
// Run           : ./p4
//

#include <stdio.h>
#include "include/integers.h"

int main(int argc, char** argv) {
    int max = 0;
    for(int i=999;i>=100;--i) {
        // if this happens, then there's no point iterating further
        // we have already reached the max number
        if((i * i) < max) {
            break;
        }
        for(int j=i;j>=100;--j) {
            int prod = i * j;
            // if this happens, then there's no point iterating further
            // in this loop
            if(prod < max) {
                break;
            }
            if(is_palindrome(prod)) {
                max = prod;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
