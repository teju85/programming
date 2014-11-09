//
// Challenge name: Penultimate Word
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/92/
// Compile       : g++ -Wall -g -o PenultimateWord PenultimateWord.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

int findPenultimate(char* str, int max) {
    bool prevSpace = true;
    int start = 0;
    int currStart = 0;
    for(int i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return start;
        }
        if(str[i] == ' ') {
            prevSpace = true;
            continue;
        }
        if(prevSpace) {
            start = currStart;
            currStart = i;
            prevSpace = false;
        }
    }
    return start;
}

void printPenultimate(char* str, int start, int max) {
    for(int i=start;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0') || (str[i] == ' ')) {
            break;
        }
        printf("%c", str[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PenultimateWord <fileContainingTestVectors>\n");
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
        int s = findPenultimate(currentLine, MAX_LINE);
        printPenultimate(currentLine, s, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
