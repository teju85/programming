//
// Challenge name: Remove Characters
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/13/
// Compile       : gcc -Wall -g -o RemoveCharacters RemoveCharacters.c
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192


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

int findComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

int findSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ' ') {
            return start;
        }
    }
    return start;
}


int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int i, j, len, rem, src;

    if(argc != 2) {
        printf("USAGE: RemoveCharacters <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        src = rem = findComma(currentLine, 0, len);
        rem = findSpace(currentLine, rem+1, len);
        for(j=0;j<src;j++) {
            for(i=rem+1;i<len;i++) {
                if(currentLine[i] == currentLine[j]) {
                    break;
                }
            }
            if(i >= len) {
                printf("%c", currentLine[j]);
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
