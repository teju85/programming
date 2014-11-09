//
// Challenge name: Problem 32
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=32
// Compile       : g++ -Wall -g -o p32 p32.cpp
// Run           : ./p32
//

#include <stdio.h>
#include <map>

std::map<int, bool> prods;


void _updateHist(int a, int* hist) {
    while(a) {
        int r = a % 10;
        a /= 10;
        hist[r]++;
    }
}

bool is1to9Pandigital(int a, int b, int c) {
    int hist[10];
    for(int i=0;i<10;++i) {
        hist[i] = 0;
    }
    _updateHist(a, hist);
    _updateHist(b, hist);
    _updateHist(c, hist);
    if(hist[0] != 0) {
        return false;
    }
    for(int i=1;i<10;++i) {
        if(hist[i] != 1) {
            return false;
        }
    }
    return true;
}

int singleDigit() {
    int sum = 0;
    // for single digit multiplicand, multiplier has to be 4 digits!
    for(int i=1;i<=9;++i) {
        for(int j=1000;j<=9999;++j) {
            int k = i * j;
            if((k < 1000) || (k > 9999)) {
                continue;
            }
            if(is1to9Pandigital(i, j, k) && (prods.find(k) == prods.end())) {
                prods[k] = true;
                sum += k;
                printf("%d * %d = %d\n", i, j, k);
            }
        }
    }
    return sum;
}

int doubleDigit() {
    int sum = 0;
    // for double digit multiplicand, multiplier has to be 3 digits!
    for(int i=10;i<=99;++i) {
        for(int j=100;j<=999;++j) {
            int k = i * j;
            if((k < 1000) || (k > 9999)) {
                continue;
            }
            if(is1to9Pandigital(i, j, k) && (prods.find(k) == prods.end())) {
                prods[k] = true;
                sum += k;
                printf("%d * %d = %d\n", i, j, k);
            }
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    int sum = singleDigit() + doubleDigit();
    printf("sum = %d\n", sum);
    return 0;
}
