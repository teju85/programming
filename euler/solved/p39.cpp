//
// Challenge name: Problem 39
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=39
// Compile       : g++ -Wall -g -o p39 p39.cpp
// Run           : ./p39
//

#include <stdio.h>
#include "include/integers.h"
#define LIMIT 1000

int numSolutions(int p) {
    int num = 0;
    for(int a=1;a<=p;++a) {
        for(int b=1;b<=p;++b) {
            int c = p - a - b;
            if((c * c) == ((a * a) + (b * b))) {
                ++num;
            }
        }
    }
    return num;
}

int main(int argc, char** argv) {
    int max = 0;
    int maxp = 0;
    // sum of pythagorean triplets is always even!
    for(int p=2;p<=LIMIT;p+=2) {
        int sols = numSolutions(p);
        if(sols > max) {
            max = sols;
            maxp = p;
        }
    }
    printf("numSolutions=%d p=%d\n", max, maxp);
    return 0;
}
