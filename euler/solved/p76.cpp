//
// Challenge name: Problem 76
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=76
// Compile       : g++ -Wall -g -o p76 p76.cpp
// Run           : ./p76
//

#include <stdio.h>
#define TOTAL 100
#define INT long long int
INT parts[TOTAL+1][TOTAL+1];

void initialize() {
    for(INT i=0;i<=TOTAL;++i) {
        for(INT j=0;j<=TOTAL;++j) {
            parts[i][j] = 0;
        }
    }
}

INT findNumWays(INT k, INT n) {
    if(k > n) {
        return 0;
    }
    if(k == n) {
        return 1;
    }
    if(parts[n][k] > 0) {
        return parts[n][k];
    }
    INT total = findNumWays(k+1, n) + findNumWays(k, n-k);
    parts[n][k] = total;
    return total;
}

INT numWays(INT sum) {
    return findNumWays(1, sum);
}

int main(int argc, char** argv) {
    initialize();
    // -1 because we need to use atleast 2 numbers
    printf("%lld\n", numWays(TOTAL)-1);
    return 0;
}
