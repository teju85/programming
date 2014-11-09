//
// Challenge name: Lettercase Percentage Ratio
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/147/
// Compile       : g++ -Wall -g -o LettercasePercentageRatio LettercasePercentageRatio.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

bool isLower(char c) {
    return ((c >= 'a') && (c <= 'z'));
}

bool isUpper(char c) {
    return ((c >= 'A') && (c <= 'Z'));
}

void printRatio(char* str, int len) {
    int upper, lower;
    upper = lower = 0;
    for(int i=0;i<len;++i) {
        if(isLower(str[i])) {
            ++lower;
        }
        else if(isUpper(str[i])) {
            ++upper;
        }
    }
    printf("lowercase: %.2f uppercase: %.2f\n",
           ((lower * 100.0f) / len), ((upper * 100.0f) / len));
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: LettercasePercentageRatio <fileContainingTestVectors>\n");
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
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        printRatio(currentLine, len);
    }
    fclose(fp);
    return 0;
}
