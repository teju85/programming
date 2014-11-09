//
// Challenge name: Even Numbers
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/100/
// Compile       : g++ -Wall -g -o EvenNumbers EvenNumbers.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: EvenNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = 0;
        fscanf(fp, "%d", &num);
        if(num == 0) {
            continue;
        }
        printf("%d\n", (num & 0x1)? 0 : 1);
    }
    fclose(fp);
    return 0;
}
