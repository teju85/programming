//
// Challenge name: Sudoku
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/78/
// Compile       : g++ -Wall -g -o sudoku sudoku.cpp
//

#include <stdio.h>

template <typename T>
T sqrtInt(T in) {
    T out;
    in = (in + 1) >> 1;
    for(out=0;in>out;in-=out++);
    return out;
}

bool isValidBoard(int** board, int N) {
    int sqN = sqrtInt(N);
    if(sqN * sqN  !=  N) {
        return false;
    }
    int expectedSum = (N * (N + 1)) >> 1;
    // row-wise
    for(int i=0;i<N;++i) {
        int sum = 0;
        for(int j=0;j<N;++j) {
            sum += board[i][j];
        }
        if(sum != expectedSum) {
            return false;
        }
    }
    // column-wise
    for(int i=0;i<N;++i) {
        int sum = 0;
        for(int j=0;j<N;++j) {
            sum += board[j][i];
        }
        if(sum != expectedSum) {
            return false;
        }
    }
    // block-wise
    for(int i=0;i<sqN;++i) {
        for(int j=0;j<sqN;++j) {
            int x = i * sqN;
            int y = j * sqN;
            int sum = 0;
            for(int k=0;k<sqN;++k) {
                for(int m=0;m<sqN;++m) {
                    sum += board[x+k][y+m];
                }
            }
            if(sum != expectedSum) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: sudoku <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int N = 0;
        int first = 0;
        fscanf(fp, "%d;%d", &N, &first);
        if(N <= 0) {
            continue;
        }
        int** board = new int*[N];
        for(int i=0;i<N;++i) {
            board[i] = new int[N];
            for(int j=0;j<N;++j) {
                if((i == 0) && (j == 0)) {
                    continue;
                }
                fscanf(fp, ",%d", &(board[i][j]));
            }
        }
        board[0][0] = first;
        printf("%s\n", isValidBoard(board, N)? "True" : "False");
        for(int i=0;i<N;++i) {
            delete board[i];
        }
        delete board;
    }
    fclose(fp);
    return 0;
}
