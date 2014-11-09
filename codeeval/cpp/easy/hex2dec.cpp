//
// Challenge name: Hex to Decimal
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/67/
// Compile       : g++ -Wall -g -o hex2dec hex2dec.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: hex2dec <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = -1;
        fscanf(fp, "%x", &num);
        if(num == -1) {
            continue;
        }
        printf("%d\n", num);
    }
    fclose(fp);
    return 0;
}
