//
// Challenge name: Stepwise Word
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/202/
// Compile       : g++ -Wall -g -o StepwiseWord StepwiseWord.cpp
//

#include <stdio.h>
#define MAX_LINE 4096

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

void stepwise(char* str, int len) {
    int maxLen = -1;
    int maxPos = -1;
    int space = 0;
    int start = 0;
    while(space < len) {
        space = findNextSpace(str, start, len);
        int len = space - start;
        if(len > maxLen) {
            maxLen = len;
            maxPos = start;
        }
        space += 1;
        start = space;
    }
    printf("%c", str[maxPos]);
    for(int i=1;i<maxLen;++i) {
        printf(" ");
        for(int j=0;j<i;++j) {
            printf("*");
        }
        printf("%c", str[maxPos+i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: StepwiseWord <fileContainingTestVectors>\n");
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
        stepwise(currentLine, len);
    }
    fclose(fp);
    return 0;
}
