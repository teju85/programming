//
// Challenge name: Longest Word
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/111/
// Compile       : g++ -Wall -g -o LongestWord LongestWord.cpp
//

#include <stdio.h>
#define MAX_LINE 1024

int longestWord(char* str, int max) {
    int longestStart = 0;
    int longest = 0;
    int currentLen = 0;
    int start = 0;
    for(int i=0;i<max;++i) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            if(longest < currentLen) {
                longest = currentLen;
                longestStart = start;
            }
            return longestStart;
        }
        if(str[i] == ' ') {
            if(longest < currentLen) {
                longest = currentLen;
                longestStart = start;
            }
            currentLen = 0;
            start = i + 1;
            continue;
        }
        ++currentLen;
    }
    return longestStart;
}

void printLongestWord(char* str, int start, int max) {
    for(int i=start;i<max;++i) {
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
        printf("USAGE: LongestWord <fileContainingTestVectors>\n");
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
        int start = longestWord(currentLine, MAX_LINE);
        printLongestWord(currentLine, start, MAX_LINE);
    }
    fclose(fp);
    return 0;
}
