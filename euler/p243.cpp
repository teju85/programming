//
// Challenge name: Problem 243
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=243
// Compile       : g++ -Wall -g -o p243 p243.cpp
// Run           : ./p243
//

#include <stdio.h>
#define INT long long int
#define TOTIENT_INT INT
#include "include/totient.h"
#define NUM 15499
#define DEN 94744
#define LIMIT 10000

int main(int argc, char** argv) {
    EulerTotient etot(LIMIT);
    float ratio = ((float)NUM) / DEN;
    INT num;
    for(num=2;num<=LIMIT;++num) {
        INT tot = etot.get_totient(num);
        float rat = ((float)tot) / (num - 1);
        if(rat < ratio) {
            printf("n=%lld phi(n)=%lld ratio=%f\n", num, tot, rat);
            break;
        }
    }
    return 0;
}
