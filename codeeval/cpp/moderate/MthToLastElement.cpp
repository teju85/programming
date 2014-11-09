//
// Challenge name: Mth to last element
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/10/
// Compile       : gcc -Wall -g -o MthToLastElement MthToLastElement.c
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

int getInt(char* str, int start, int end) {
    int i, factor, sum;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    return sum;
}

int findNextSpace(char* str, int start, int len) {
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
    char chars[MAX_LINE];
    int len, M, i, j, numC;

    if(argc != 2) {
        printf("USAGE: MthToLastElement <fileContainingTestVectors>\n");
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
        // value of M
        M = 0;
        for(i=len-1;i>=0;i--) {
            if(currentLine[i] == ' ') {
                currentLine[i] = '\0';
                M = getInt(currentLine, i+1, len);
                len = i;
                break;
            }
        }
        // each character
        numC = 0;
        for(i=0;i<len;) {
            chars[numC] = currentLine[i];
            numC++;
            j = findNextSpace(currentLine, i, len);
            i = j + 1;
        }
        if(numC < M) {
            continue;
        }
        printf("%c\n", chars[numC-M]);
    }
    fclose(fp);
    return 0;
}
