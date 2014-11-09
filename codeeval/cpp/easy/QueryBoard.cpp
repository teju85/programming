//
// Challenge name: Query Board
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/87/
// Compile       : g++ -Wall -g -o QueryBoard QueryBoard.cpp
//

#include <stdio.h>
#include <string.h>
#define BOARD_SIZE 256
#define CMD_MAX_SIZE 16

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard() {
    for(int i=0;i<BOARD_SIZE;++i) {
        for(int j=0;j<BOARD_SIZE;++j) {
            board[i][j] = 0;
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    initBoard();
    if(argc != 2) {
        printf("USAGE: QueryBoard <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char cmd[CMD_MAX_SIZE];
        int read = fscanf(fp, "%s", cmd);
        if(read <= 0) {
            continue;
        }
        if(!strcmp(cmd, "SetRow")) {
            int row, val;
            fscanf(fp, "%d%d", &row, &val);
            char c = (char)val;
            for(int i=0;i<BOARD_SIZE;++i) {
                board[row][i] = c;
            }
        }
        else if(!strcmp(cmd, "SetCol")) {
            int col, val;
            fscanf(fp, "%d%d", &col, &val);
            char c = (char)val;
            for(int i=0;i<BOARD_SIZE;++i) {
                board[i][col] = c;
            }
        }
        else if(!strcmp(cmd, "QueryRow")) {
            int row;
            int sum = 0;
            fscanf(fp, "%d", &row);
            for(int i=0;i<BOARD_SIZE;++i) {
                sum += (int)board[row][i];
            }
            printf("%d\n", sum);
        }
        else if(!strcmp(cmd, "QueryCol")) {
            int col;
            int sum = 0;
            fscanf(fp, "%d", &col);
            for(int i=0;i<BOARD_SIZE;++i) {
                sum += (int)board[i][col];
            }
            printf("%d\n", sum);
        }
        else {
            printf("Bad command! %s\n", cmd);
        }
    }
    fclose(fp);
    return 0;
}
