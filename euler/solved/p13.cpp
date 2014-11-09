//
// Challenge name: Problem 13
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=13
// Compile       : g++ -Wall -g -o p13 p13.cpp
// Run           : ./p13 p13.txt
//

#include <stdio.h>
#include "include/characters.h"
#include "include/integers.h"
#define MAX_COLS 100

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p13 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    // summation buffer
    char out[MAX_COLS+1];
    for(int i=0;i<=MAX_COLS;++i) {
        out[i] = '0';
    }
    int rows;
    int cols;
    int num_d;
    char str[MAX_COLS+1];
    fscanf(fp, "%d%d%d", &rows, &cols, &num_d);
    for(int i=0;i<rows;++i) {
        fscanf(fp, "%s", str);
        reverse_str(str, 0, cols-1);
        int carry = 0;
        int j = 0;
        for(;j<cols;++j) {
            int d = char2digit(str[j]) + char2digit(out[j]) + carry;
            carry = d / 10;
            d %= 10;
            out[j] = (char) ('0' + d);
        }
        while(carry) {
            int d = char2digit(out[j]) + carry;
            carry = d / 10;
            d %= 10;
            out[j] = (char) ('0' + d);
            ++j;
        }
    }
    fclose(fp);
    // go to the first non-zero location
    int j = MAX_COLS;
    while(out[j] == '0') {
        --j;
    }
    for(int i=0;i<num_d;++i) {
        printf("%c", out[j-i]);
    }
    printf("\n");
    return 0;
}
