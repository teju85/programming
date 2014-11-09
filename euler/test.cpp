#include <stdio.h>
#include "include/integers.h"

#define INT unsigned long long int

//p290
// Findings:
//  1. 'sum' has to be divisible by 9
//  2. So, 'n' also has to be divisible by 9
int main(int argc, char** argv) {
    for(INT n=9;n<=1000;n+=9) {
        INT n137 = n * 137;
        INT sum = sum_of_digits<INT>(n);
        if(sum == sum_of_digits<INT>(n137)) {
            printf("n=%llu n137=%llu sum=%llu\n", n, n137, sum);
        }
    }
    return 0;
}
