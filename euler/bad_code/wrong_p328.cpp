//
// Challenge name: Problem 328
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=328
// Compile       : g++ -Wall -g -o p328 p328.cpp
// Run           : ./p328
//
#include <stdio.h>

#define INT int
#define LIMIT 50
#define DEBUG
INT g_cost[LIMIT+1];
INT num_q[LIMIT+1]; // max number of questions asked in the worst case

void initialize() {
    g_cost[0] = 0;
    g_cost[1] = 0;
    g_cost[2] = 1;
    g_cost[3] = 2;
    for(int i=3;i<=LIMIT;++i) {
        g_cost[i] = -1;
    }
    num_q[0] = 0;
    num_q[1] = 0;
    num_q[2] = 1;
    num_q[3] = 1;
    for(int i=3;i<=LIMIT;++i) {
        num_q[i] = -1;
    }
}

INT get_cost(int num) { // evaluates C(num)
    if(g_cost[num] >= 0) {
        return g_cost[num];
    }
    INT cost = 0x7fffffff;
    INT numq = -1;
    // anything below the binary tree cannot give us the
    // best worst-case strategy.
    for(int i=(num>>1)+1;i<num;++i) {
        /* cost */
        INT lower = g_cost[i-1];
        INT higher = g_cost[num-i];
        // for every of those questions asked, there's an extra penalty
        if(higher) {
            higher += (num_q[num-i] * i);
        }
        INT total = (lower > higher)? i + lower  :  i + higher;
        /* questions */
        INT lower_q = num_q[i-1];
        INT higher_q = num_q[num-i];
        INT nq = (lower_q > higher_q)? 1 + lower_q  :  1 + higher_q;
        /* actual cost and number of questions asked */
        if(cost > total) {
            cost = total;
            numq = nq;
        }
        else if(cost == total) {
            if(nq < numq) {
                numq = nq;
            }
        }
        /* debug */
#ifdef DEBUG
        printf("lo=%d hi=%d p=%d l=%d h=%d t=%d\n",
                   1, num, i, lower, higher, total);
        //printf("n=%d i=%d h=%d l=%d t=%d hq=%d lq=%d q=%d\n",
        //       num, i, higher, lower, total, higher_q, lower_q, nq);
#endif
    }
    g_cost[num] = cost;
    num_q[num] = numq;
    return cost;
}

int main(int argc, char** argv) {
    initialize();
    for(int i=0;i<=LIMIT;++i) {
        printf("C(%d)=%d\n", i, get_cost(i));
    }
    return 0;
}
