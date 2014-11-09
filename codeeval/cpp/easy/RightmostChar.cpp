//
// Challenge name: Rightmost Char
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/31/
// Compile       : g++ -Wall -g -o RightmostChar RightmostChar.cpp
//

#include <stdio.h>
// assuming that line contains only 4096 characters
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

int findNextComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int i, len;
    char search;

    if(argc != 2) {
        printf("USAGE: RightmostChar <fileContainingTestVectors>\n");
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
        i = findNextComma(currentLine, 0, len);
        search = currentLine[i+1];
        for(i--;i>=0;i--) {
            if(currentLine[i] == search) {
                break;
            }
        }
        if(i < 0) {
            i = -1;
        }
        printf("%d\n", i);
    }
    fclose(fp);
    return 0;
}
