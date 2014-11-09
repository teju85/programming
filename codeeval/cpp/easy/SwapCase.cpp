//
// Challenge name: Swap Case
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/96/
// Compile       : g++ -Wall -g -o SwapCase SwapCase.cpp
//

#include <stdio.h>
#include <ctype.h>
#define MAX_LINE 1024

void swapCase(char* str, int max) {
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return;
        }
        int v = (int)str[i];
        if(isupper(v)) {
            str[i] = (char)tolower(v);
        }
        else if(islower(v)) {
            str[i] = (char)toupper(v);
        }
    }
    return;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SwapCase <fileContainingTestVectors>\n");
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
        swapCase(currentLine, MAX_LINE);
        printf("%s\n", currentLine);
    }
    fclose(fp);
    return 0;
}
