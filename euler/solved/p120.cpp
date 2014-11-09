//
// Challenge name: Problem 120
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=120
// Compile       : g++ -Wall -g -o p120 p120.cpp
// Run           : ./p120
//

#include <stdio.h>

#define START 3
#define LIMIT 1000
#define INT unsigned long long int


int main(int argc, char** argv) {
    INT sum_rmax = 0;
    for(int a=START;a<=LIMIT;++a) {
        // by simple analysis, I found that the maximum possible
        // repetition cycle for 'a' is '2a'.
        int limit = a << 1;
        int a2 = a * a;
        int rmax = -1;
        int n1 = a - 1;
        int n2 = a + 1;
        int r1 = 1;
        int r2 = 1;
        for(int n=1;n<=limit;++n) {
            r1 = (r1 * n1) % a2;
            r2 = (r2 * n2) % a2;
            int r = (r1 + r2) % a2;
            if(r > rmax) {
                rmax = r;
            }
        }
        sum_rmax += (INT)rmax;
    }
    printf("%llu\n", sum_rmax);
    return 0;
}
