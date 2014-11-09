//
// Challenge name: Problem 95
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=95
// Compile       : g++ -Wall -g -o p95 p95.cpp
// Run           : ./p95
//

#include <stdio.h>
#include <map>
#include "include/integers.h"
#include "include/seive.h"
#define LIMIT 1000000
#define INT int
using namespace std;

INT sumProps[LIMIT];

void initialize() {
    for(INT i=0;i<LIMIT;++i) {
        sumProps[i] = -1;
        chainLen[i] = -1;
    }
    sumProps[0] = 0;
    sumProps[1] = 1;
    sumProps[2] = 1;
    chainLen[0] = 0;
    chainLen[1] = 0;
    chainLen[2] = 0;
}

INT getSumProps(INT num) {
    if(sumProps[num] >= 0) {
        return sumProps[num];
    }
    sumProps[num] = sum_of_proper_divisors<INT>(num);
    return sumProps[num];
}

INT chainLength(INT num, const eratos& se) {
    if(chainLen[num] >= 0) {
        return chainLen[num];
    }
    INT len = 0;
    map<INT, bool> nums;
    INT orig = num;
    while(true) {
        INT sum = getSumProps(num);
        // found the chain
        if(sum == orig) {
            break;
        }
        ++len;
        if(nums.find(sum) != nums.end()) {
            return 0;
        }
        if(sum >= LIMIT) {
            return 0;
        }
        nums[sum] = true;
        //printf("-> %d %d\n", num, sum);
        num = sum;
    }
    return len;
}

//@todo: optimize the run-time of this program!
int main(int argc, char** argv) {
    INT maxLen = -1;
    INT maxNum = 0;
    eratos se(LIMIT+1);
    se.generate_seive();
    initialize();
    for(INT num=2;num<LIMIT;++num) {
        if(se.is_prime(num)) {
            continue;
        }
        INT len = chainLength(num, se);
        if(len > 0) {
            printf("num=%d chain=%d\n", num, len);
        }
        if(len > maxLen) {
            maxLen = len;
            maxNum = num;
        }
    }
    printf("len=%d num=%d\n", maxLen, maxNum);
    return 0;
}
