//
// Challenge name: Bit Positions
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/19/
// Compile       : g++ -Wall -g -o BitPositions BitPositions.c
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int num, p1, p2, last1, last2;

    if(argc != 2) {
        printf("USAGE: BitPositions <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        num = -1;
        fscanf(fp, "%d,%d,%d", &num, &p1, &p2);
        if(num == -1) {
            continue;
        }
        last1 = (num >> (p1 - 1)) & 0x1;
        last2 = (num >> (p2 - 1)) & 0x1;
        if(last1 == last2) {
            printf("true\n");
        }
        else {
            printf("false\n");
        }
    }
    fclose(fp);
    return 0;
}
