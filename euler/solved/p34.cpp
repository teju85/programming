//
// Challenge name: Problem 34
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=34
// Compile       : g++ -Wall -g -o p34 p34.cpp
// Run           : ./p34
//

#include <stdio.h>

int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int sum_of_fac_of_digits(int num) {
    if(num <= 0) {
        return 1;
    }
    int sum = 0;
    while(num) {
        int d = num % 10;
        num /= 10;
        sum += fac[d];
    }
    return sum;
}

int main(int argc, char** argv) {
    // beyond this limit, the sum will exceed the number, think why ;)
    int limit = 9 * fac[9];
    int sum = 0;
    // 1, 2 are not considered as per the problem!
    for(int i=3;i<=limit;++i) {
        if(sum_of_fac_of_digits(i) == i) {
            sum += i;
        }
    }
    printf("%d\n", sum);
    return 0;
}
