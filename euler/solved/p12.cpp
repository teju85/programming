//
// Challenge name: Problem 12
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=12
// Compile       : g++ -Wall -g -o p12 p12.cpp
// Run           : ./p12
//

#include <stdio.h>
#include "include/integers.h"
#define NUM_DIVS 500

int main(int argc, char** argv) {
    for(int i=1;;++i) {
        int sum = triangle_sum<int>(i);
        int num = num_divisors<int>(sum);
        if(num >= NUM_DIVS) {
            printf("%d\n", sum);
            break;
        }
    }
    return 0;
}
