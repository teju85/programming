//
// Challenge name: Decimal To Binary
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/27/
// Compile       : g++ -Wall -g -o DecimalToBinary DecimalToBinary.cpp
//

#include <stdio.h>

void printBinary(int num) {
    if(num == 0) {
        return;
    }
    printBinary(num >> 1);
    printf("%d", (num & 0x1));
}

int main(int argc, char** argv) {
    FILE* fp;
    int num;

    if(argc != 2) {
        printf("USAGE: DecimalToBinary <fileContainingTestVectors>\n");
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
        if(num == 0) {
            printf("0\n");
            continue;
        }
        printBinary(num);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
