//
// Challenge name: Shortest Repetition
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/107/
// Compile       : g++ -Wall -g -o ShortestRepetition ShortestRepetition.cpp
//

#include <stdio.h>
#define MAX_LINE 128

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

bool compare(const char* s1, const char* s2, int len) {
    for(int i=0;i<len;++i) {
        if(s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

bool isRepetition(const char* s, int len, int repLen) {
    for(int i=repLen;i<len;i+=repLen) {
        if(!compare(s, s+i, repLen)) {
            return false;
        }
    }
    return true;
}

int shortestRep(const char* s, int len) {
    int limit = len >> 1;
    for(int i=1;i<=limit;++i) {
        if((len % i) != 0) {
            continue;
        }
        if(isRepetition(s, len, i)) {
            return i;
        }
    }
    return len;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ShortestRepetition <fileContainingTestVectors>\n");
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
        printf("%d\n", shortestRep(currentLine, len));
    }
    fclose(fp);
    return 0;
}
