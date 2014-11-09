//
// Challenge name: Problem 1
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=1
// Compile       : g++ -Wall -g -o p1 p1.cpp
// Run           : ./p1
//

#include <stdio.h>
#include "include/integers.h"

int main(int argc, char** argv) {
    int max = 999;
    int n1 = 3;
    int n2 = 5;
    int n3 = lcm(n1, n2);
    int sum_n1 = n1 * triangle_sum<int>(max/n1);
    int sum_n2 = n2 * triangle_sum<int>(max/n2);
    int sum_n3 = n3 * triangle_sum<int>(max/n3);
    int sum = sum_n1 + sum_n2 - sum_n3;
    printf("%d\n", sum);
    return 0;
}
