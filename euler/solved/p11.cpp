//
// Challenge name: Problem 11
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=11
// Compile       : g++ -Wall -g -o p11 p11.cpp
// Run           : ./p11 p11.txt
//

#include <stdio.h>
#include "include/comparisons.h"
#define CONSECUTIVE 4


int max_along_horizontal(int** arr, int N) {
    int max = -1;
    int limit = N - CONSECUTIVE;
    for(int i=0;i<N;++i) {
        int prod;
        for(int j=0;j<limit;++j) {
            prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[i][j+k];
            }
            max = max2<int>(max, prod);
        }
    }
    return max;
}

int max_along_vertical(int** arr, int N) {
    int max = -1;
    int limit = N - CONSECUTIVE;
    for(int j=0;j<N;++j) {
        int prod;
        for(int i=0;i<limit;++i) {
            prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[i+k][j];
            }
            max = max2<int>(max, prod);
        }
    }
    return max;
}

int max_along_diagonal(int** arr, int N) {
    int max = -1;
    // top to bottom
    for(int d=CONSECUTIVE-1;d<N;++d) {
        // forward-slash
        int limit = d - (CONSECUTIVE - 1);
        for(int i=0;i<=limit;++i) {
            int prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[i+k][d-i-k];
            }
            max = max2<int>(max, prod);
            prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[N-1-i-k][d-i-k];
            }
            max = max2<int>(max, prod);
        }
        // backward-slash
        limit = d - CONSECUTIVE - 1;
        for(int i=0;i<=limit;++i) {
            int prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[i+k][N-1-d+i+k];
            }
            max = max2<int>(max, prod);
        }
    }
    // bottom to top
    for(int d=N-CONSECUTIVE;d>0;--d) {
        // forward-slash
        int limit = d - (CONSECUTIVE - 1);
        for(int i=0;i<=limit;++i) {
            int prod = 1;
            for(int k=0;k<CONSECUTIVE;++k) {
                prod *= arr[i+k][d-i-k];
            }
            max = max2<int>(max, prod);
        }
    }
    return max;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p11 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    int N;
    int** arr;
    fscanf(fp, "%d", &N);
    arr = new int*[N];
    for(int i=0;i<N;++i) {
        arr[i] = new int[N];
        for(int j=0;j<N;++j) {
            fscanf(fp, "%d", &(arr[i][j]));
        }
    }
    fclose(fp);
    int maxh = max_along_horizontal(arr, N);
    int maxv = max_along_vertical(arr, N);
    int maxd = max_along_diagonal(arr, N);
    int max = max3<int>(maxh, maxv, maxd);
    printf("%d\n", max);
    for(int i=0;i<N;++i) {
        delete arr[i];
    }
    delete arr;
    return 0;
}
