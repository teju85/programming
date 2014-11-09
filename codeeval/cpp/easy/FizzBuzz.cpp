//
// Challenge name: Fizz Buzz
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/1/
// Compile       : g++ -Wall -g -o FizzBuzz FizzBuzz.cpp
//

#include <stdio.h>

typedef enum {
    FIZZ,
    BUZZ,
    BOTH,
    NONE
} TYPE_FB;

void printRes(TYPE_FB type, int val, int max) {
    switch(type) {
    case FIZZ:
        printf("F");
        break;
    case BUZZ:
        printf("B");
        break;
    case BOTH:
        printf("FB");
        break;
    case NONE:
        printf("%d", val);
        break;
    }
    if(val < max) {
        printf(" ");
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    int A, B, N, i;
    if(argc != 2) {
        printf("USAGE: FizzBuzz <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        A = -1;
        fscanf(fp, "%d%d%d", &A, &B, &N);
        if(A <= 0) {
            continue;
        }
        for(i=1;i<=N;i++) {
            if(!(i % A)) {
                if(!(i % B)) {
                    printRes(BOTH, i, N);
                    continue;
                }
                printRes(FIZZ, i, N);
                continue;
            }
            if(!(i % B)) {
                printRes(BUZZ, i, N);
                continue;
            }
            printRes(NONE, i, N);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
