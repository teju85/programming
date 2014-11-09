//
// Challenge name: Problem 6
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=6
// Compile       : g++ -Wall -g -o p6 p6.cpp
// Run           : ./p6
//

#include <stdio.h>
#include "include/integers.h"

int main(int argc, char** argv) {
    int num = 100;
    int s1 = triangle_sum<int>(num);
    s1 *= s1;
    int s2 = sum_of_squares<int>(num);
    printf("%d\n", s1 - s2);
    return 0;
}
