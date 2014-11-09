//
// Challenge name: Word Search
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/65/
// Compile       : g++ -Wall -g -o wordSearch wordSearch.cpp
//

#include <stdio.h>
#define MAX_LINE 4096
#define NUM_ROWS 3
#define NUM_COLS 4

char board[NUM_ROWS][NUM_COLS] = {
    {'A', 'B', 'C', 'E'},
    {'S', 'F', 'C', 'S'},
    {'A', 'D', 'E', 'E'}
};
bool visited[NUM_ROWS][NUM_COLS];

void resetVisited() {
    for(int i=0;i<NUM_ROWS;++i) {
        for(int j=0;j<NUM_COLS;++j) {
            visited[i][j] = false;
        }
    }
}

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

bool gridSearch(char* line, int len, int start, int i, int j) {
    if(start >= len) {
        return true;
    }
    if((i < 0) || (i >= NUM_ROWS) || (j < 0) || (j >= NUM_COLS)) {
        return false;
    }
    if(line[start] != board[i][j]) {
        return false;
    }
    if(visited[i][j]) {
        return false;
    }
    visited[i][j] = true;
    if(gridSearch(line, len, start+1, i-1, j)) {
        return true;
    }
    if(gridSearch(line, len, start+1, i, j-1)) {
        return true;
    }
    if(gridSearch(line, len, start+1, i+1, j)) {
        return true;
    }
    if(gridSearch(line, len, start+1, i, j+1)) {
        return true;
    }
    visited[i][j] = false;
    return false;
}

bool isStringFound(char* line, int len) {
    for(int i=0;i<NUM_ROWS;++i) {
        for(int j=0;j<NUM_COLS;++j) {
            resetVisited();
            if(gridSearch(line, len, 0, i, j)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int len;
    if(argc != 2) {
        printf("USAGE: wordSearch <fileContainingTestVectors>\n");
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
        printf("%s\n", isStringFound(currentLine, len)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
