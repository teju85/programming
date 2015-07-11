//
// Challenge name: Swap Numbers
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/196/
// Compile       : g++ -Wall -g -o SwapNumbers SwapNumbers.cpp
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

void swapNumbers(char* str, int len) {
    int start = 0;
    int space = 0;
    while(space < len) {
        space = findNextSpace(str, space, len);
        int loc = space - 1;
        char tmp = str[loc];
        str[loc] = str[start];
        str[start] = tmp;
        space += 1;
        start = space;
    }
    printf("%s\n", str);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SwapNumbers <fileContainingTestVectors>\n");
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
        swapNumbers(currentLine, len);
    }
    fclose(fp);
    return 0;
}
