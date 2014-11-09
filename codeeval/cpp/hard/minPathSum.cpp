//
// Challenge name: Minimum Path Sum
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/72/
// Compile       : g++ -Wall -g -o minPathSum minPathSum.cpp
//

#include <stdio.h>

int minPathSum(int** mat, int n) {
    for(int i=1;i<n;++i) {
        mat[0][i] += mat[0][i-1];
        mat[i][0] += mat[i-1][0];
    }
    for(int i=1;i<n;++i) {
        for(int j=1;j<n;++j) {
            int x = mat[i-1][j];
            int y = mat[i][j-1];
            mat[i][j] += (x < y)? x : y;
        }
    }
    return mat[n-1][n-1];
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: minPathSum <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int n = 0;
        fscanf(fp, "%d", &n);
        if(n <= 0) {
            continue;
        }
        int** mat = new int*[n];
        for(int i=0;i<n;++i) {
            mat[i] = new int[n];
            fscanf(fp, "%d", &(mat[i][0]));
            for(int j=1;j<n;++j) {
                fscanf(fp, ",%d", &(mat[i][j]));
            }
        }
        printf("%d\n", minPathSum(mat, n));
        for(int i=0;i<n;++i) {
            delete mat[i];
        }
        delete mat;
    }
    fclose(fp);
    return 0;
}
