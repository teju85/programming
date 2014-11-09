//
// Challenge name: Problem 92
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=92
// Compile       : g++ -Wall -g -o p92 p92.cpp
// Run           : ./p92
//

#include <stdio.h>
#include "include/integers.h"
#define LIMIT 10000000
#define INT int

int main(int argc, char** argv) {
    INT num = 0;
    for(INT i=1;i<LIMIT;++i) {
        INT sum = i;
        while((sum != 1) && (sum != 89)) {
            sum = sum_of_square_of_digits<int>(sum);
        }
        if(sum == 89) {
            ++num;
        }
    }
    printf("%d\n", num);
    return 0;
}
