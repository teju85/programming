//
// Challenge name: Matrix Rotation
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/178/
// Compile       : g++ -Wall -g -o MatrixRotation MatrixRotation.cpp
//

#include <stdio.h>
#define MAX 1024

char matrix[MAX];
char outMatrix[MAX];

int readMatrix(FILE* fp) {
    char c;
    int dim = 0;
    while(true) {
        if(fscanf(fp, "%c", &c) == 0) {
            break;
        }
        if(feof(fp)) {
            break;
        }
        if(c == ' ') {
            continue;
        }
        if(c == '\r') {
            continue;
        }
        if(c == '\n') {
            break;
        }
        matrix[dim] = c;
        ++dim;
    }
    matrix[dim] = '\0';
    return dim;
}

int squareRoot(int len) {
    for(int i=1;i<MAX;++i) {
        if((i*i) == len) {
            return i;
        }
    }
    return -1;
}

void printMatrix(int len) {
    printf("%c", outMatrix[0]);
    for(int i=1;i<len;++i) {
        printf(" %c", outMatrix[i]);
    }
    printf("\n");
}

void rotateMatrix(int N) {
    for(int i=0,k=0;i<N;++i) {
        for(int j=0;j<N;++j,++k) {
            int m = (N * j) + N - 1 - i;
            outMatrix[m] = matrix[k];
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MatrixRotation <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int len = readMatrix(fp);
        if(len <= 0) {
            continue;
        }
        int dim = squareRoot(len);
        rotateMatrix(dim);
        printMatrix(len);
    }
    fclose(fp);
    return 0;
}
