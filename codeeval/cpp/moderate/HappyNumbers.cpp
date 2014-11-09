//
// Challenge name: Happy Numbers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/39/
// Compile       : gcc -Wall -g -o HappyNumbers HappyNumbers.c
//

#include <stdio.h>

// why this number?
//  . number 'n' containing 'm' digits.
//  . its sum of square of digits is <= 9 * 9 * m = 81 * m
//  . assuming 32b signed integers.
//  . m <= 10   which means, max sum-square-of-digits = 810.
//  . using pigeon hole principle, after 810 iterations, there
//    should be repetition (worst case).
//  . just made it to nearest minimum power of two, to be safe.
#define MAX_LOOP 1024


int digitSquareSum(int n) {
    int sum, v;
    for(sum=0;n;n/=10) {
        v = n % 10;
        sum += (v * v);
    }
    return sum;
}

int cycleFound(int* history, int num, int len) {
    int i;
    for(i=0;i<=len;i++) {
        if(history[i] == num) {
            return 1;
        }
    }
    return 0;
}

int isHappy(int n) {
    int history[MAX_LOOP];
    int i, j;
    if(n == 1) {
        return 1;
    }
    history[0] = n;
    for(i=1;i<MAX_LOOP;i++) {
        j = digitSquareSum(n);
        if(j == 1) {
            return 1;
        }
        if(cycleFound(history, j ,i)) {
            return 0;
        }
        history[i] = j;
        n = j;
    }
    // will not reach 1, so lets assume it to be not a happy number!
    // this case should never occur
    return 0;
}

int main(int argc, char** argv) {
    FILE* fp;
    int num;

    if(argc != 2) {
        printf("USAGE: HappyNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        num = -1;
        fscanf(fp, "%d", &num);
        if(num == -1) {
            continue;
        }
        printf("%d\n", isHappy(num)? 1 : 0);
    }
    fclose(fp);
    return 0;
}
