//
// Challenge name: Counting Primes
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/63/
// Compile       : g++ -Wall -g -o countingPrimes countingPrimes.cpp
//

#include <stdio.h>

template <typename T>
T sqrtInt(T in) {
    T out;
    in = (in + 1) >> 1;
    for(out=0;in>out;in-=out++);
    return out;
}

template <typename T>
T isPrime(T a) {
    if(!(a % 2)) {
        return false;
    }
    T sq = sqrtInt(a);
    for(T i=3;i<=sq;i+=2) {
        if(!(a % i)) {
            return false;
        }
    }
    return true;
}

int countPrimes(int n, int m) {
    int num = 0;
    if(n == 2) {
        ++num;
        ++n;
    }
    // even numbers cant be prime
    if(!(n & 0x1)) {
        ++n;
    }
    while(n <= m) {
        if(isPrime(n)) {
            ++num;
        }
        n += 2;
    }
    return num;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: countingPrimes <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    int n, m;
    while(!feof(fp)) {
        n = m = 0;
        fscanf(fp, "%d,%d", &n, &m);
        if((n == 0) || (m == 0)) {
            continue;
        }
        printf("%d\n", countPrimes(n, m));
    }
    fclose(fp);
    return 0;
}
