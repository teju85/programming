//
// Challenge name: Minesweeper
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/79/
// Compile       : g++ -Wall -g -o minesweeper minesweeper.cpp
//

#include <stdio.h>

bool isMine(char** mine, int M, int N, int i, int j) {
    if(i < 0)  return false;
    if(j < 0)  return false;
    if(i >= M) return false;
    if(j >= N) return false;
    return (mine[i][j] == '*');
}

int numNeighboringMines(char** mine, int M, int N, int i, int j) {
    int num = 0;
    if(isMine(mine, M, N, i-1, j-1)) ++num;
    if(isMine(mine, M, N, i-1, j  )) ++num;
    if(isMine(mine, M, N, i-1, j+1)) ++num;
    if(isMine(mine, M, N, i  , j-1)) ++num;
    if(isMine(mine, M, N, i  , j+1)) ++num;
    if(isMine(mine, M, N, i+1, j-1)) ++num;
    if(isMine(mine, M, N, i+1, j  )) ++num;
    if(isMine(mine, M, N, i+1, j+1)) ++num;
    return num;
}

void printMineCount(char** mine, int M, int N) {
    for(int i=0;i<M;++i) {
        for(int j=0;j<N;++j) {
            if(isMine(mine, M, N, i, j)) {
                printf("*");
                continue;
            }
            printf("%d", numNeighboringMines(mine, M, N, i, j));
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: minesweeper <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int M, N;
        M = N = 0;
        fscanf(fp, "%d,%d;", &M, &N);
        if(N <= 0) {
            continue;
        }
        char** mine = new char*[M];
        for(int i=0;i<M;++i) {
            mine[i] = new char[N];
            for(int j=0;j<N;++j) {
                fscanf(fp, "%c", &(mine[i][j]));
            }
        }
        printMineCount(mine, M, N);
        for(int i=0;i<M;++i) {
            delete mine[i];
        }
        delete mine;
    }
    fclose(fp);
    return 0;
}
