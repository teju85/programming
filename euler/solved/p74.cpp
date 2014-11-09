//
// Challenge name: Problem 74
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=74
// Compile       : g++ -Wall -g -o p74 p74.cpp
// Run           : ./p74
//

#include <stdio.h>
#include <map>

#define LIMIT 1000000
#define MAX 3000000
#define LEN 60

int fac[10];
int chainLen[MAX];

void initialize() {
    for(int i=0;i<=10;++i) {
        int prod = 1;
        for(int j=1;j<=i;++j) {
            prod *= j;
        }
        fac[i] = prod;
    }
    chainLen[0] = 1;
    for(int i=1;i<MAX;++i) {
        chainLen[i] = -1;
    }
}

int digitFactorial(int num) {
    int sum = 0;
    while(num) {
        int r = num % 10;
        num /= 10;
        sum += fac[r];
    }
    return sum;
}

int findChainLen(int num) {
    if(chainLen[num] >= 0) {
        return chainLen[num];
    }
    std::map<int, bool> nums;
    int save = num;
    int len = 0;
    while(chainLen[num] < 0) {
        nums[num] = true;
        num = digitFactorial(num);
        ++len;
        if(nums.find(num) != nums.end()) {
            chainLen[save] = len;
            break;
        }
        if(chainLen[num] >= 0) {
            chainLen[save] = len + chainLen[num];
            break;
        }
    }
    return chainLen[save];
}

int main(int argc, char** argv) {
    int num = 0;
    initialize();
    for(int i=1;i<LIMIT;++i) {
        if(findChainLen(i) == LEN) {
            ++num;
        }
    }
    printf("%d\n", num);
    return 0;
}
