//
// Challenge name: Problem 31
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=31
// Compile       : g++ -Wall -g -o p31 p31.cpp
// Run           : ./p31
//

#include <stdio.h>
#define TOTAL 200

int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
int numCoins = 8;
int numWays = 0;

void findNumWays(int currentCoinId, int sum) {
    if(currentCoinId < 0) {
        return;
    }
    if(sum < 0) {
        return;
    } 
    for(int i=0;i<=sum;i+=coins[currentCoinId]) {
        int rem = sum - i;
        //printf("id=%d i=%d s=%d\n", currentCoinId, i, sum);
        if(rem == 0) {
            ++numWays;
            continue;
        }
        if(rem < 0) {
            continue;
        }
        findNumWays(currentCoinId-1, rem);
    }
}

int main(int argc, char** argv) {
    findNumWays(7, TOTAL);
    printf("%d\n", numWays);
    return 0;
}
