//
// Challenge name: Problem 42
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=42
// Compile       : g++ -Wall -g -o p42 p42.cpp
// Run           : ./p42 p42.txt
//

#include <stdio.h>
#include <string.h>
#include "include/characters.h"
#include "include/integers.h"

#define CHARS 32


bool is_triangle_word(char* name) {
    int val = sum_of_alphabets(name, strlen(name));
    return is_triangle_num(val);
}

int main(int argc, char** argv) {
    FILE* fp;
    char name[CHARS];
    if(argc != 2) {
        printf("USAGE: p42 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    int num = 0;
    while(!feof(fp)) {
        fscanf(fp, "%s", name);
        if(!feof(fp)) {
            if(is_triangle_word(name)) {
                ++num;
            }
        }
    }
    fclose(fp);
    printf("%d\n", num);
    return 0;
}
