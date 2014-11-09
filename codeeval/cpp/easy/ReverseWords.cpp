//
// Challenge name: Reverse words
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/8/
// Compile       : g++ -Wall -g -o ReverseWords ReverseWords.cpp
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

int trim(char* str, int len) {
    for(len--;len>=0;len--) {
        if(str[len] != ' ') {
            return len + 1;
        }
        str[len] = '\0';
    }
    return len + 1;
}

void reverse(char* str, int start, int end) {
    int i, j;
    char t;
    for(i=start,j=end-1;i<j;i++,j--) {
        t = str[i];
        str[i] = str[j];
        str[j] = t;
    }
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
    int i, j, len;

    if(argc != 2) {
        printf("USAGE: ReverseWords <fileContainingTestVectors>\n");
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
        len = trim(currentLine, len);
        if(len <= 0) {
            continue;
        }
        reverse(currentLine, 0, len);
        for(i=0;i<len;) {
            j = findNextSpace(currentLine, i, len);
            reverse(currentLine, i, j);
            i = j + 1;
        }
        len = trim(currentLine, len);
        printf("%s\n", currentLine);
    }
    fclose(fp);
    return 0;
}
