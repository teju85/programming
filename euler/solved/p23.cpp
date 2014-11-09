//
// Challenge name: Problem 23
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=23
// Compile       : g++ -Wall -g -o p23 p23.cpp
// Run           : ./p23
//

#include <stdio.h>
#include "include/integers.h"

#define MAX_NUM 28123
char abundant[MAX_NUM+1];
char is_sum[MAX_NUM+1];

bool is_abundant(int num) {
    if(num > MAX_NUM) {
        return false;
    }
    if(abundant[num] >= 0) {
        return abundant[num];
    }
    int sum = sum_of_proper_divisors<int>(num);
    abundant[num] = (sum > num)? 1 : 0;
    return abundant[num];
}

void initialize() {
    abundant[0] = 0;
    abundant[1] = 0;
    for(int i=2;i<=MAX_NUM;++i) {
        abundant[i] = -1;
    }
    for(int i=2;i<=MAX_NUM;++i) {
        is_abundant(i);
    }
    for(int i=0;i<=MAX_NUM;++i) {
        is_sum[i] = 0;
    }
}

int main(int argc, char** argv) {
    initialize();
    for(int i=0;i<=MAX_NUM;++i) {
        if(is_abundant(i)) {
            for(int j=i;(i+j)<=MAX_NUM;++j) {
                if(is_abundant(j)) {
                    is_sum[i+j] = 1;
                }
            }
        }
    }
    int sum = 0;
    for(int i=0;i<=MAX_NUM;++i) {
        if(!is_sum[i]) {
            sum += i;
        }
    }
    printf("%d\n", sum);
    return 0;
}
