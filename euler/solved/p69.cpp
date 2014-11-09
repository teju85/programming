//
// Challenge name: Problem 69
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=69
// Compile       : g++ -Wall -g -o p69 p69.cpp
// Run           : ./p69
//

#include <stdio.h>
#define LIMIT 1000000
#define INT int
#define TOTIENT_INT INT
#include "include/totient.h"

int main(int argc, char** argv) {
    EulerTotient etot(LIMIT);
    float max = 0;
    INT n = 0;
    for(INT i=2;i<=LIMIT;++i) {
        INT tot = etot.get_totient(i);
        float rat = ((float) i) / tot;
        if(rat > max) {
            max = rat;
            n = i;
        }
    }
    printf("num=%d ratio=%f\n", n, max);
    return 0;
}
