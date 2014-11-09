//
// Challenge name: Jolly Jumpers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/43/
// Compile       : gcc -Wall -g -o JollyJumpers JollyJumpers.c
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int n0, n1, i, sumDiff, n, expectedDiff, j;

    if(argc != 2) {
        printf("USAGE: JollyJumpers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        n = -1;
        fscanf(fp, "%d", &n);
        if(n <= 0) {
            continue;
        }
        sumDiff = 0;
        expectedDiff = (n * (n - 1)) >> 1;
        fscanf(fp, "%d", &n0);
        for(i=1;i<n;i++) {
            fscanf(fp, "%d", &n1);
            j = (n1 > n0)? n1 - n0 : n0 - n1;
            sumDiff += j;
            n0 = n1;
        }
        printf("%s\n", (sumDiff == expectedDiff)? "Jolly" : "Not jolly");
    }
    fclose(fp);
    return 0;
}
