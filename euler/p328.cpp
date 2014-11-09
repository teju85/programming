//
// Challenge name: Problem 328
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=328
// Compile       : g++ -Wall -g -o p328 p328.cpp
// Run           : ./p328
//
#include <stdio.h>

#define INT int
#define LIMIT 1000
//#define DEBUG
INT g_cost[LIMIT+1];  // cost for the case (1, N)

void initialize() {
    g_cost[0] = 0;
    g_cost[1] = 0;
    g_cost[2] = 1;
    g_cost[3] = 2;
    g_cost[4] = 4;
    for(int i=5;i<=LIMIT;++i) {
        g_cost[i] = -1;
    }
}

INT find_pivot(INT s, INT e) {
    INT pivot = 0;
    INT diff = 0x7fffffff;
    for(INT p=e-1;p>=s;p-=2) {
        INT left = (((p - 1) * p) >> 1) - (((s - 1) * s) >> 1);
        INT right = ((e * (e + 1)) >> 1) - ((p * (p + 1)) >> 1);
        INT ab = (left > right)? left - right : right - left;
        if(ab < diff) {
            diff = ab;
            pivot = p;
        }
    }
    return pivot;
}

INT get_cost(INT num, INT penalty) {
    if(num <= 1) {
        return 0;
    }
    if(num == 2) {
        return (penalty + 1);
    }
    if(num == 3) {
        return (penalty + 2);
    }
    if(num == 4) {
        return ((penalty << 1) + 4);
    }
    if(!penalty  &&  (g_cost[num] >= 0)) {
        return g_cost[num];
    }
    INT cost = 0x7fffffff;
    INT last = num >> 1;
    if(penalty) {
        INT pivot = find_pivot(penalty+1, penalty+num) - penalty;
        //printf("p=%d n=%d pi=%d\n", penalty, num, pivot);
        INT low = get_cost(pivot-1, penalty);
        INT high = get_cost(num-pivot, penalty+pivot);
        INT total = (low > high)? low : high;
        cost = (penalty + pivot + total);
        return cost;
    }
    // anything below the binary tree cannot give us the
    // best worst-case strategy.
    for(INT pivot=num-1;pivot>=last;pivot-=2) {
        INT low = get_cost(pivot-1, penalty);
        INT high = get_cost(num-pivot, penalty+pivot);
        INT total = (low > high)? low : high;
#ifdef DEBUG
        printf("p=%d l=%d h=%d t=%d\n", pivot, low, high, total);
#endif
        total += (penalty + pivot);
        if(total < cost) {
            cost = total;
        }
    }
    if(!penalty) {
        g_cost[num] = cost;
    }
    return cost;
}

INT worst_cost(INT num) {
    return get_cost(num, 0);
}

int main(int argc, char** argv) {
    initialize();
    INT sum = 0;
    for(INT i=0;i<=LIMIT;++i) {
        INT val = worst_cost(i);
        //printf("C(%d)=%d\n", i, val);
        sum += val;
    }
    printf("%d\n", sum);
    return 0;
}
