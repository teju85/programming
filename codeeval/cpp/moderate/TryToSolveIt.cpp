//
// Challenge name: TRY TO SOLVE IT
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/226/
// Compile       : g++ -Wall -g -o TryToSolveIt TryToSolveIt.cpp
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

char decode(char c) {
    if((c >= 'a') && (c <= 'f')) {
        return (c - 'a' + 'u');
    } else if((c >= 'g') && (c <= 'm')) {
        return (c - 'g' + 'n');
    } else if((c >= 'u') && (c <= 'z')) {
        return (c - 'u' + 'a');
    } else if((c >= 'n') && (c <= 't')) {
        return (c - 'n' + 'g');
    }
    return c;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TryToSolveIt <fileContainingTestVectors>\n");
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
        for(int i=0;i<len;++i) {
            printf("%c", decode(currentLine[i]));
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
