//
// Challenge name: String Mask
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/199/
// Compile       : g++ -Wall -g -o StringMask StringMask.cpp
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

int findNextSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ' ') {
            return start;
        }
    }
    return start;
}

inline char toUpper(char in) {
    return (in - 'a' + 'A');
}

void stringMask(const char* str, const char* mask, int len) {
    for(int i=0;i<len;++i) {
        if(mask[i] == '0') {
            printf("%c", str[i]);
        }
        else {
            printf("%c", toUpper(str[i]));
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: StringMask <fileContainingTestVectors>\n");
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
        int space = findNextSpace(currentLine, 0, len);
        stringMask(currentLine, currentLine+space+1, space);
    }
    fclose(fp);
    return 0;
}
