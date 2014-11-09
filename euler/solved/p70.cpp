//
// Challenge name: Problem 70
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=70
// Compile       : g++ -Wall -g -o p70 p70.cpp
// Run           : ./p70
//

#include <stdio.h>
#include "include/integers.h"
#include "include/seive.h"
#define LIMIT 10000000
#define INT int
#define TOTIENT_INT INT
#include "include/totient.h"

int main(int argc, char** argv) {
    EulerTotient etot(LIMIT);
    float min = LIMIT;
    INT n = 0;
    for(INT i=2;i<=LIMIT;++i) {
        INT tot = etot.get_totient(i);
        if(is_permutation<INT>(tot, i)) {
            float rat = ((float) i) / tot;
            if(rat < min) {
                min = rat;
                n = i;
            }
        }
    }
    printf("num=%d ratio=%f totient=%d\n", n, min, etot.get_totient(n));
    return 0;
}
