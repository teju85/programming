//
// Challenge name: Trailing String
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/32/
// Compile       : g++ -Wall -g -o TrailingString TrailingString.cpp
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
    int i, j, len, slen, dlen;

    if(argc != 2) {
        printf("USAGE: TrailingString <fileContainingTestVectors>\n");
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
        slen = findNextComma(currentLine, 0, len);
        dlen = len - slen - 1;
        if(dlen > slen) {
            printf("0\n");
            continue;
        }
        for(i=slen-1,j=len-1;j>slen;j--,i--) {
            if(currentLine[i] != currentLine[j]) {
                break;
            }
        }
        if(j != slen) {
            printf("0\n");
        }
        else {
            printf("1\n");
        }
    }
    fclose(fp);
    return 0;
}
