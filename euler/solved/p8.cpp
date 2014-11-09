//
// Challenge name: Problem 8
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=8
// Compile       : g++ -Wall -g -o p8 p8.cpp
// Run           : ./p8 p8.txt
//

#include <stdio.h>
#include "include/characters.h"
#define MAX_CHARS 8192
#define CONSECUTIVE 5

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p8 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    int num_digits;
    fscanf(fp, "%d", &num_digits);
    char digits[MAX_CHARS];
    for(int i=0;i<num_digits;++i) {
        fscanf(fp, "%c", &(digits[i]));
    }
    fclose(fp);
    int max=-1;
    int limit = num_digits - CONSECUTIVE;
    for(int i=0;i<limit;++i) {
        int prod = 1;
        for(int j=0;j<CONSECUTIVE;++j) {
            prod *= char2digit(digits[i+j]);
        }
        if(prod > max) {
            max = prod;
        }
    }
    printf("%d\n", max);
    return 0;
}
