//
// Challenge name: Problem 21
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=21
// Compile       : g++ -Wall -g -o p21 p21.cpp
// Run           : ./p21
//

#include <stdio.h>
#include "include/integers.h"
#define LIMIT 10000

int main(int argc, char** argv) {
    int arr[LIMIT+1];
    arr[0] = 0;
    for(int i=0;i<=LIMIT;++i) {
        arr[i] = sum_of_proper_divisors<int>(i);
    }
    int sum = 0;
    for(int a=1;a<=LIMIT;++a) {
        int b = arr[a];
        if(b > LIMIT) {
            continue;
        }
        int b1 = arr[b];
        if((a != b) && (a == b1)) {
            sum += (a + b);
            arr[a] = arr[b] = 0;
            printf("%d,%d\n", a, b);
        }
    }
    printf("%d\n", sum);
    return 0;
}
