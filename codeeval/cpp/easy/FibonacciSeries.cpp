//
// Challenge name: Fibonacci Series
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/22/
// Compile       : g++ -Wall -g -o FibonacciSeries FibonacciSeries.c
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int num, i, n1, n2, t;

    if(argc != 2) {
        printf("USAGE: MultiplesOfANumber <fileContainingTestVectors>\n");
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
        n1 = 1;
        n2 = 0;
        if(num == 0) {
            printf("%d\n", n2);
            continue;
        }
        if(num == 1) {
            printf("%d\n", n1);
            continue;
        }
        for(i=2;i<=num;i++) {
            t = n1 + n2;
            n2 = n1;
            n1 = t;
        }
        printf("%d\n", n1);
    }
    fclose(fp);
    return 0;
}
