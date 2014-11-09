//
// Challenge name: Capitalize Words
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/93/
// Compile       : g++ -Wall -g -o CapitalizeWords CapitalizeWords.cpp
//

#include <stdio.h>
#include <ctype.h>
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

void capitalize(char* str, int len) {
    bool prevSpace = true;
    for(int i=0;i<len;++i) {
        if((str[i] == ' ') || (str[i] == '\t')) {
            prevSpace = true;
            continue;
        }
        if(prevSpace) {
            str[i] = (char) toupper((int)str[i]);
            prevSpace = false;
            continue;
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CapitalizeWords <fileContainingTestVectors>\n");
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
        capitalize(currentLine, len);
        printf("%s\n", currentLine);
    }
    fclose(fp);
    return 0;
}
