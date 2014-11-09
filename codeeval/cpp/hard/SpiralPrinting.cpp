//
// Challenge name: Spiral Printing
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/57/
// Compile       : g++ -Wall -g -o SpiralPrinting SpiralPrinting.cpp
//

#include <stdio.h>
#include <string>

using namespace std;


void printSpiral(string** mat, int R, int C, int s) {
    //printf("R=%d C=%d s=%d\n", R, C, s);
    // first row
    for(int i=s;i<C-s;++i) {
        printf("%s ", mat[s][i].c_str());
    }
    // last column
    for(int i=s+1;i<R-s;++i) {
        printf("%s ", mat[i][C-1-s].c_str());
    }
    // last row
    if((R-1-s) > s) {
        for(int i=C-2-s;i>s;--i) {
            printf("%s ", mat[R-1-s][i].c_str());
        }
    }
    // first column
    for(int i=R-1-s;i>s;--i) {
        printf("%s ", mat[i][s].c_str());
    }
    ++s;
    int s2 = s << 1;
    if((R <= s2) || (C <= s2)) {
        return;
    }
    printSpiral(mat, R, C, s);
}

int main(int argc, char** argv) {
    FILE* fp;
    int R, C;
    if(argc != 2) {
        printf("USAGE: SpiralPrinting <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        R = C = -1;
        fscanf(fp, "%d;%d;", &R, &C);
        if((R <= 0) || (C <= 0)) {
            continue;
        }
        string** mat;
        char data[16];
        mat = new string*[R];
        for(int i=0;i<R;++i) {
            mat[i] = new string[C];
            for(int j=0;j<C;++j) {
                fscanf(fp, "%s", data);
                mat[i][j] = data;
            }
        }
        printSpiral(mat, R, C, 0);
        printf("\n");
        for(int i=0;i<R;++i) {
            delete [] mat[i];
        }
        delete [] mat;
    }
    fclose(fp);
    return 0;
}
