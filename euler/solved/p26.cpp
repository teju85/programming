//
// Challenge name: Problem 26
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=26
// Compile       : g++ -Wall -g -o p26 p26.cpp
// Run           : ./p26
//

#include <stdio.h>
#define LIMIT 1000
#define ITERS 10000

int quo[ITERS];
int rem[ITERS];

void initHist() {
    for(int i=0;i<ITERS;++i) {
        quo[i] = 0;
        rem[i] = 0;
    }
}

int findCycle(int iter) {
    int q = quo[iter];
    int r = rem[iter];
    for(int i=1;i<iter;++i) {
        if((quo[i] == q) && (rem[i] == r)) {
            return (iter - i);
        }
    }
    return 0;
}

int unitFraction(int d) {
    initHist();
    int q = 10;
    int iter = 0;
    printf("%d  .", d);
    while(true) {
        while(q < d) {
            q *= 10;
            printf("0");
            ++iter;
            quo[iter] = 0;
            rem[iter] = q;
        }
        ++iter;
        int r = q % d;
        q /= d;
        printf("%d", q);
        if(!r) {
            return 0;
        }
        quo[iter] = q;
        rem[iter] = r;
        int cycle = findCycle(iter);
        if(cycle > 0) {
            return cycle;
        }
        q = r * 10;
    }
    return 0;
}

int main(int argc, char** argv) {
    int max = -1;
    int maxD = -1;
    for(int d=2;d<LIMIT;++d) {
        int recur = unitFraction(d);
        printf("\n");
        if(recur > max) {
            max = recur;
            maxD = d;
        }
    }
    printf("max=%d num=%d\n", max, maxD);
    return 0;
}
