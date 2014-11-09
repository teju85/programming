//
// Challenge name: Problem 328
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=328
// Compile       : g++ -Wall -g -o p328 p328.cpp
// Run           : ./p328
//
#include <stdio.h>
#include <map>
#include <string>
using namespace std;

#define INT int
#define LIMIT 100
#define CHARS 32
//#define DEBUG

map<string, INT> worstCost;

char _str[CHARS];
char* get_str(INT l, INT h) {
    sprintf(_str, "[%d,%d]", l, h);
    return _str;
}

INT get_worst_cost(INT l, INT h) {
    string s(get_str(l, h));
    if(worstCost.find(s) == worstCost.end()) {
        return -1;
    }
    return worstCost[s];
}

void set_worst_cost(INT l, INT h, INT cost) {
    string s(get_str(l, h));
    worstCost[s] = cost;
}

INT get_min_worst_cost(INT l, INT h) {
    if(l >= h) {
        return 0;
    }
    if(l+1 == h) {
        return l;
    }
    if(l+2 == h) {
        return l+1;
    }
    if(l+3 == h) {
        return ((l << 1) + 4);
    }
    INT wc = get_worst_cost(l, h);
    if(wc >= 0) {
        return wc;
    }
    INT last = ((h - l + 1) >> 1) + l;
    INT cost = 0x7fffffff;
    for(INT pivot=h-1;pivot>=last;pivot-=2) {
        INT low = get_min_worst_cost(l, pivot-1);
        INT high = get_min_worst_cost(pivot+1, h);
        INT total = (low > high)? low : high;
#ifdef DEBUG
        if(l == 1) {
            printf("p=%d l=%d h=%d t=%d\n", pivot, low, high, total);
        }
#endif
        total += pivot;
        if(cost > total) {
            cost = total;
        }
    }
    set_worst_cost(l, h, cost);
    return cost;
}

int get_cost(int num) {
    if(num <= 1) {
        return 0;
    }
    return get_min_worst_cost(1, num);
}


int main(int argc, char** argv) {
    INT sum = 0;
    for(int i=0;i<=LIMIT;++i) {
        INT val = get_cost(i);
#ifdef DEBUG
        printf("C(%d)=%d\n", i, val);
#endif
        sum += val;
    }
    printf("%d\n", sum);
    return 0;
}
