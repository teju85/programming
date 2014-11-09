//
// Challenge name: Roman And Arabic
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/150/
// Compile       : g++ -Wall -g -o RomanAndArabic RomanAndArabic.cpp
//

#include <stdio.h>
#define MAX_LINE 32

int getRoman(char s) {
    switch(s) {
    case 'I':   return 1;
    case 'V':   return 5;
    case 'X':   return 10;
    case 'L':   return 50;
    case 'C':   return 100;
    case 'D':   return 500;
    case 'M':   return 1000;
    default:    return 0;
    }
}

int char2int(char s) {
    return ((int)(s - '0'));
}

int currentAR(char a, char r, int& prev, int& prevR) {
    int rom = getRoman(r);
    int ara = char2int(a);
    int out = rom * ara;
    if(prevR < rom) {
        out -= (2 * prev);
    }
    prev = rom * ara;
    prevR = rom;
    return out;
}

int calculate(char* str, int max) {
    int val = 0;
    int prev = 0;
    int prevR = 0;
    for(int i=0;i<max;i+=2) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            break;
        }
        val += currentAR(str[i], str[i+1], prev, prevR);
    }
    return val;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RomanAndArabic <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        printf("%d\n", calculate(currentLine, MAX_LINE));
    }
    fclose(fp);
    return 0;
}
