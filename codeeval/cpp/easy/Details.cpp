//
// Challenge name: Details
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/183/
// Compile       : g++ -Wall -g -o Details Details.cpp
//

#include <stdio.h>
#define MAX_LINE 512
#define MAX_M 32

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

int find(char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return start;
}

int count(char* str, int start, int len, char c) {
    int cnt = 0;
    for(;start<len;start++) {
        if(str[start] == c) {
            ++cnt;
        }
    }
    return cnt;
}

void getFirstYpos(const char* str, int M, int N, int* yPos) {
    for(int i=0;i<M;++i) {
        int start = i * (N+1); // N+1 to take care of ','
        int end = start + N;
        yPos[i] = -1;
        for(int j=start;j<end;++j) {
            if(str[j] == 'Y') {
                yPos[i] = j;
                break;
            }
        }
        if(yPos[i] == -1) {
            yPos[i] = end;
        }
    }
}

bool hasNextMove(const char* str, int M, int N, int* yPos) {
    for(int i=0;i<M;++i) {
        int start = i * (N+1); // N+1 to take care of ','
        if(yPos[i] == start) {
            return false;
        }
        if(str[yPos[i]-1] == 'X') {
            return false;
        }
    }
    return true;
}

void makeNextMove(const char* str, int M, int N, int* yPos) {
    for(int i=0;i<M;++i) {
        --yPos[i];
    }
}

int numMovesY(char* str, int M, int N) {
    int yPos[MAX_M];
    getFirstYpos(str, M, N, yPos);
    int cnt = 0;
    while(hasNextMove(str, M, N, yPos)) {
        makeNextMove(str, M, N, yPos);
        ++cnt;
    }
    return cnt;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Details <fileContainingTestVectors>\n");
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
        if(currentLine[0] == '\0') {
            continue;
        }
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        int N = find(currentLine, 0, len, ',');
        int M = count(currentLine, 0, len, ',') + 1;
        printf("%d\n", numMovesY(currentLine, M, N));
    }
    fclose(fp);
    return 0;
}
