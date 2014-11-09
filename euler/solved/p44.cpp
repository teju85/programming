//
// Challenge name: Problem 44
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=44
// Compile       : g++ -Wall -g -o p44 p44.cpp
// Run           : ./p44
//

#include <stdio.h>
#include "include/integers.h"

#define INT int


int main(int argc, char** argv) {
    for(INT j=2;;++j) {
        INT pj = pentagonal<INT>(j);
        for(INT k=j-2;k>0;--k) {
            INT pk = pentagonal<INT>(k);
            if(is_pentagonal<INT>(pj+pk) && is_pentagonal<INT>(pj-pk)) {
                printf("j=%d k=%d pj=%d pk=%d D=%d\n",
                       j, k, pj, pk, (pj-pk));
                return 0;
            }
        }
    }
    return 0;
}
