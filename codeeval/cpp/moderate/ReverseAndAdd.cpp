//
// Challenge name: Reverse and Add
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/45/
// Compile       : gcc -Wall -g -o ReverseAndAdd ReverseAndAdd.c
//

#include <stdio.h>

#define MAX_DIGITS 32
#define MAX_ITERS 1000

int isPalindrome(unsigned long long n) {
    unsigned long long arr[MAX_DIGITS];
    unsigned long long temp;
    int i, j;
    for(i=0,temp=n;temp;i++,temp/=10) {
        arr[i] = temp % 10;
    }
    for(i--,j=0;i>j;i--,j++) {
        if(arr[i] != arr[j]) {
            return 0;
        }
    }
    return 1;
}

unsigned long long reverse(unsigned long long n) {
    unsigned long long arr[MAX_DIGITS];
    unsigned long long temp, sum;
    int i;
    for(i=0,temp=n;temp;i++,temp/=10) {
        arr[i] = temp % 10;
    }
    for(i--,sum=0,temp=1;i>=0;i--,temp*=10) {
        sum += (temp * arr[i]);
    }
    return sum;
}

int main(int argc, char** argv) {
    FILE* fp;
    unsigned long long N;
    int numSteps;

    if(argc != 2) {
        printf("USAGE: ReverseAndAdd <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        N = 0;
        numSteps = 0;
        fscanf(fp, "%llu", &N);
        if(N == 0) {
            continue;
        }
        for(numSteps=1;numSteps<=MAX_ITERS;numSteps++) {
            N += reverse(N);
            if(isPalindrome(N)) {
                printf("%d %llu\n", numSteps, N);
                break;
            }
        }
    }
    fclose(fp);
    return 0;
}
