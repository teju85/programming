//
// Challenge name: Multiples of a Number
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/18/
// Compile       : gcc -Wall -g -o MultiplesOfANumber MultiplesOfANumber.c
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int po2, num;

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
        po2 = -1;
        fscanf(fp, "%d,%d", &num, &po2);
        if(po2 < 1) {
            continue;
        }
        while(po2 < num) {
            po2 <<= 1;
        }
        printf("%d\n", po2);
    }
    fclose(fp);
    return 0;
}
