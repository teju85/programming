//
// Challenge name: Prime Numbers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/46/
// Compile       : gcc -Wall -g -o PrimeNumbers PrimeNumbers.c
//

#include <stdio.h>

int isPrime(unsigned int n) {
    unsigned int i, t;
    if(!(n & 0x1)) {
        return 0;
    }
    t = n >> 1;
    for(i=3;i<=t;i+=2) {
        if(!(n % i)) {
            return 0;
        }
        t = n / i;
    }
    return 1;
}

unsigned int numPrinted = 0;
void printPrime(int p) {
    if(!numPrinted) {
        printf("%u", p);
    }
    else {
        printf(",%u", p);
    }
    numPrinted++;
}

int main(int argc, char** argv) {
    FILE* fp;
    unsigned int N, i;

    if(argc != 2) {
        printf("USAGE: PrimeNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        numPrinted = 0;
        N = 0;
        fscanf(fp, "%u", &N);
        if(!N) {
            continue;
        }
        if(N >= 2) {
            printPrime(2);
        }
        for(i=3;i<N;i+=2) {
            if(isPrime(i)) {
                printPrime(i);
            }
        }
        if(numPrinted) {
            printf("\n");
        }
    }
    fclose(fp);
    return 0;
}
