//
// Challenge name: Problem 81
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=81
// Compile       : g++ -Wall -g -o p81 p81.cpp
// Run           : ./p81 p81.txt
//

#include <stdio.h>
#include "include/comparisons.h"

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p81 <fileContainingTestVectors>\n");
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
    for(int i=1;i<dim;++i) {
        mat[0][i] += mat[0][i-1];
        mat[i][0] += mat[i-1][0];
    }
    for(int i=1;i<dim;++i) {
        for(int j=1;j<dim;++j) {
            mat[i][j] += min2<int>(mat[i][j-1], mat[i-1][j]);
        }
    }
    // evaluate
    printf("%d\n", mat[dim-1][dim-1]);
    // clean
    for(int i=0;i<dim;++i) {
        delete mat[i];
    }
    delete mat;
    return 0;
}
