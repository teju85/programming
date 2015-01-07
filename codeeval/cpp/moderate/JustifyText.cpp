//
// Challenge name: Justify Text
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/177/
// Compile       : g++ -Wall -g -o JustifyText JustifyText.cpp
//

#include <stdio.h>
#define MAX_LINE 2048
#define MAX 80

void printLine(const char* str, int len, int numSpaces, bool just) {
    if(!just) {
        for(int i=0;i<len;++i) {
            printf("%c", str[i]);
        }
        printf("\n");
        return;
    }
    int extra = MAX - len;
    int neededSpaces = extra / numSpaces;
    int extraSpaces = extra % numSpaces;
    for(int i=0;i<len;++i) {
        if(str[i] == ' ') {
            int count = (extraSpaces > 0)? neededSpaces+1 : neededSpaces;
            for(int j=0;j<count;++j) {
                printf(" ");
            }
            --extraSpaces;
        }
        printf("%c", str[i]);
    }
    printf("\n");
}

void justify(const char* str, int max) {
    int prevStart = 0;
    int prevSpace = 0;
    int numSpaces = 0;
    for(int i=0;i<max;++i) {
        int len = i - prevStart;
        if((str[i] == '\0') || (str[i] == '\r') || (str[i] == '\n')) {
            if(len > MAX) {
                int count = prevSpace - prevStart - 1;
                --numSpaces; // ignore the space at the end of this line
                printLine(str+prevStart, count, numSpaces, true);
                prevStart = prevSpace;
                numSpaces = 0;
            }
            printLine(str+prevStart, i-prevStart, 0, false);
            break;
        }
        if(str[i] != ' ') {
            continue;
        }
        if(len > MAX) {
            int count = prevSpace - prevStart - 1;
            printLine(str+prevStart, count, numSpaces, true);
            prevStart = prevSpace;
            numSpaces = 0;
        }
        else if(len == MAX) {
            int count = i - prevStart;
            printLine(str+prevStart, count, numSpaces, true);
            prevStart = i + 1;
            numSpaces = 0;
        }
        else {
            ++numSpaces;
        }
        prevSpace = i + 1;
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: JustifyText <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    char currentLine[MAX_LINE];
    while(!feof(fp)) {
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        justify(currentLine, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
