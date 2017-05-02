//
// Challenge name: DOUBLE TROUBLE
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/215/
// Compile       : g++ -Wall -g -o DoubleTrouble DoubleTrouble.cpp
//

#include <stdio.h>
#define MAX_LINE 512

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

long long count(const char* str, int len) {
    if(len % 2 != 0) {
        return 0;
    }
    int sLen = len >> 1;
    const char* first = str;
    const char* second = str + sLen;
    long long cnt = 1;
    for(int i=0;i<sLen;++i) {
        if(first[i] == second[i]) {
            if(first[i] == '*') {
                cnt *= 2;
            }
        } else {
            if((first[i] == 'A') || (first[i] == 'B')) {
                if(second[i] != '*') return 0;
            }
        }
    }
    return cnt;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DoubleTrouble <fileContainingTestVectors>\n");
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
        printf("%lld\n", count(currentLine, len));
    }
    fclose(fp);
    return 0;
}
