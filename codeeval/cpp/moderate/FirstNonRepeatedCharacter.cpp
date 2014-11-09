//
// Challenge name: First Non-Repeated Character
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/12/
// Compile       : gcc -Wall -g -o FirstNonRepeatedCharacter FirstNonRepeatedCharacter.c
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

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int i, j, len;

    if(argc != 2) {
        printf("USAGE: FirstNonRepeatedCharacter <fileContainingTestVectors>\n");
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
        for(i=0;i<len;i++) {
            for(j=0;j<len;j++) {
                if((i != j) && (currentLine[i] == currentLine[j])) {
                    break;
                }
            }
            if(j >= len) {
                printf("%c\n", currentLine[i]);
                break;
            }
        }
        if(i >= len) {
            printf("\n");
        }
    }
    fclose(fp);
    return 0;
}
