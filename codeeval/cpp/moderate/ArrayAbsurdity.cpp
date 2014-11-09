//
// Challenge name: Array Absurdity
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/41/
// Compile       : gcc -Wall -g -o ArrayAbsurdity ArrayAbsurdity.c
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int N, i, number, sum, expectedSum;

    if(argc != 2) {
        printf("USAGE: ArrayAbsurdity <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        N = -1;
        fscanf(fp, "%d;", &N);
        if(N <= 0) {
            continue;
        }
        sum = 0;
        expectedSum = ((N - 2) * (N - 1)) >> 1;
        fscanf(fp, "%d", &(number));
        sum += number;
        for(i=1;i<N;i++) {
            fscanf(fp, ",%d", &(number));
            sum += number;
        }
        // difference between 'expectedSum' and 'sum' is the duplicate!
        printf("%d\n", (sum - expectedSum));
    }
    fclose(fp);
    return 0;
}
