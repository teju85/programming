//
// Challenge name: Multiply Lists
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/113/
// Compile       : g++ -Wall -g -o MultiplyLists MultiplyLists.cpp
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

int findSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ' ') {
            return start;
        }
    }
    return start;
}

int getInt(char* str, int start, int end) {
    int i, factor, sum;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    return sum;
}

int findPipe(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == '|') {
            return start;
        }
    }
    return start;
}

void multiplyAndPrint(char* str, int len) {
    int pipe = findPipe(str, 0, len);
    int prevStart1=0, start1=0;
    int prevStart2=pipe+2, start2=pipe+2;
    bool isFirst = true;
    while(true) {
        start1 = findSpace(str, prevStart1, pipe);
        start2 = findSpace(str, prevStart2, len);
        if((start1 > pipe) || (start2 > len)) {
            break;
        }
        if(!isFirst) {
            printf(" ");
        }
        if(isFirst) {
            isFirst = false;
        }
        int a = getInt(str, prevStart1, start1);
        int b = getInt(str, prevStart2, start2);
        printf("%d", (a * b));
        prevStart1 = start1 + 1;
        prevStart2 = start2 + 1;
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MultiplyLists <fileContainingTestVectors>\n");
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
        multiplyAndPrint(currentLine, len);
    }
    fclose(fp);
    return 0;
}
