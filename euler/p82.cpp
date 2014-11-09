//
// Challenge name: Problem 82
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=82
// Compile       : g++ -Wall -g -o p82 p82.cpp
// Run           : ./p82 p82.txt
//

#include <stdio.h>
#include "include/comparisons.h"

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p82 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    // read the matrix
    int dim;
    fscanf(fp, "%d", &dim);
    int** mat = new int*[dim];
    for(int i=0;i<dim;++i) {
        mat[i] = new int[dim];
        for(int j=0;j<dim;++j) {
            fscanf(fp, "%d", &(mat[i][j]));
        }
    }
    fclose(fp);
    // initialize
    int minVal = 0x7fffffff;
    int minPos = -1;
    for(int row=0;row<dim;++row) {
        int val = mat[row][1] + mat[row][0];
        if(val < minVal) {
            minVal = val;
            minPos = row;
        }
    }
    int minSum = minVal;
    // evaluate
    for(int col=2;col<dim;++col) {
        minVal = minSum + mat[minPos][col];
        int pos = minPos;
        // up
        int pathSum = minSum;
        for(int row=minPos-1;row>=0;--row) {
            pathSum += mat[row][col-1];
            int val = pathSum + mat[row][col];
            if(val < minVal) {
                minVal = val;
                pos = row;
            }
        }
        // down
        pathSum = minSum;
        for(int row=minPos+1;row<dim;++row) {
            pathSum += mat[row][col-1];
            int val = pathSum + mat[row][col];
            if(val < minVal) {
                minVal = val;
                pos = row;
            }
        }
        minSum = minVal;
        minPos = pos;
    }
    printf("%d\n", minSum);
    // clean
    for(int i=0;i<dim;++i) {
        delete mat[i];
    }
    delete mat;
    return 0;
}
