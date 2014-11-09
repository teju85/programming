//
// Challenge name: Problem 345
// Difficulty    : hard
// Link          : http://projecteuler.net/index.php?section=problems&id=345
// Compile       : g++ -Wall -g -o p345 p345.cpp
// Run           : ./p345 p345.txt
//
#include <stdio.h>
#include <vector>
using namespace std;



// location of an element in the matrix
struct Location {
    int r;
    int c;
};
typedef vector<Location> Locations;
typedef Locations::iterator Litr;



////// matrix of integers //////
typedef int Element;
struct Matrix {
    int R;
    int C;
    Element** data;

    Matrix() { R = C = 0; data = NULL; }
    Matrix(const Matrix& mat);
    Matrix(const Matrix& mat, Location& l1, Location& l2);
    ~Matrix();
    int max_in_row(int row) const;
    int max_in_col(int col) const;
    int subtract_max_in_row(int row);
    int subtract_max_in_col(int col);
    bool unique_in_row(int row, int num) const;
    bool unique_in_col(int col, int num) const;
    int find_in_row(int row, int num) const;
    int find_in_col(int col, int num) const;
    void print() const;
};
Matrix::Matrix(const Matrix& mat) {
    R = mat.R;
    C = mat.C;
    if((R <= 0) || (C <= 0)) {
        data = NULL;
        return;
    }
    data = new Element*[R];
    for(int i=0;i<R;++i) {
        data[i] = new Element[C];
        for(int j=0;j<C;++j) {
            data[i][j] = mat.data[i][j];
        }
    }
}
Matrix::Matrix(const Matrix& mat, Location& l1, Location& l2) {
    R = (l1.r == l2.r)? mat.R - 1  :  mat.R - 2;
    C = (l1.c == l2.c)? mat.C - 1  :  mat.C - 2;
    if((R <= 0) || (C <= 0)) {
        data = NULL;
        return;
    }
    data = new Element*[R];
    for(int i=0,i1=0;i<mat.R;++i) {
        if((i == l1.r) || (i == l2.r)) {
            continue;
        }
        data[i1] = new Element[C];
        for(int j=0,j1=0;j<mat.C;++j) {
            if((j == l1.c) || (j == l2.c)) {
                continue;
            }
            data[i1][j1] = mat.data[i][j];
            ++j1;
        }
        ++i1;
    }
}
Matrix::~Matrix() {
    if(data != NULL) {
        for(int i=0;i<R;++i) {
            delete data[i];
        }
        delete data;
        data = NULL;
    }
}
int Matrix::max_in_row(int row) const {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    int max = 0xffffffff;
    for(int i=0;i<C;++i) {
        if(max < data[row][i]) {
            max = data[row][i];
        }
    }
    return max;
}
int Matrix::max_in_col(int col) const {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    int max = 0x80000000;
    for(int i=0;i<R;++i) {
        if(max < data[i][col]) {
            max = data[i][col];
        }
    }
    return max;
}
int Matrix::subtract_max_in_row(int row) {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    int max = max_in_row(row);
    for(int i=0;i<C;++i) {
        data[row][i] -= max;
    }
    return max;
}
int Matrix::subtract_max_in_col(int col) {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    int max = max_in_col(col);
    for(int i=0;i<R;++i) {
        data[i][col] -= max;
    }
    return max;
}
bool Matrix::unique_in_row(int row, int num) const {
    if((R <= 0) || (C <= 0)) {
        return false;
    }
    int found = 0;
    for(int i=0;i<C;++i) {
        if(data[row][i] == num) {
            ++found;
        }
    }
    return (found == 1);
}
bool Matrix::unique_in_col(int col, int num) const {
    if((R <= 0) || (C <= 0)) {
        return false;
    }
    int found = 0;
    for(int i=0;i<R;++i) {
        if(data[i][col] == num) {
            ++found;
        }
    }
    return (found == 1);
}
int Matrix::find_in_row(int row, int num) const {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    for(int i=0;i<C;++i) {
        if(data[row][i] == num) {
            return i;
        }
    }
    return -1;
}
int Matrix::find_in_col(int col, int num) const {
    if((R <= 0) || (C <= 0)) {
        return -1;
    }
    for(int i=0;i<R;++i) {
        if(data[i][col] == num) {
            return i;
        }
    }
    return -1;
}
void Matrix::print() const {
    if((R <= 0) || (C <= 0)) {
        return;
    }
    for(int i=0;i<R;++i) {
        for(int j=0;j<C;++j) {
            printf("%4d ", data[i][j]);
        }
        printf("\n");
    }
}
////// matrix of integers //////


// REF:
//  http://en.wikipedia.org/wiki/Hungarian_algorithm#Matrix_interpretation
void maximize_assignment(Matrix& m) {
    Matrix mat(m);
    bool* rows = new bool[mat.R];
    bool* cols = new bool[mat.C];
    // step 1
    printf("Step1:\n");
    for(int i=0;i<mat.R;++i) {
        mat.subtract_max_in_row(i);
    }
    mat.print();
    printf("\n");
    // step 2
    printf("Step2:\n");
    for(int i=0;i<mat.C;++i) {
        mat.subtract_max_in_col(i);
    }
    mat.print();
    printf("\n");
    // step 3a
    printf("Step3a:\n");
    for(int i=0;i<mat.R;++i) {
        rows[i] = mat.unique_in_row(i, 0);
    }
    for(int i=0;i<mat.C;++i) {
        cols[i] = mat.unique_in_col(i, 0);
    }
    printf("Rows:\n");
    for(int i=0;i<mat.R;++i) {
        printf("%d ", rows[i]);
    }
    printf("\n");
    printf("Cols:\n");
    for(int i=0;i<mat.C;++i) {
        printf("%d ", cols[i]);
    }
    printf("\n");
    printf("\n");
    // step 3b
    printf("Step3b:\n");
    for(int i=0;i<mat.R;++i) {
        if(!rows[i]) {
        }
    }
    printf("\n");
    // cleanup
    delete rows;
    delete cols;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p345 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    // get the matrix
    Matrix mat;
    fscanf(fp, "%d%d", &(mat.R), &(mat.C));
    mat.data = new Element*[mat.R];
    for(int i=0;i<mat.R;++i) {
        mat.data[i] = new Element[mat.C];
        for(int j=0;j<mat.C;++j) {
            fscanf(fp, "%d", &(mat.data[i][j]));
        }
    }
    // work on the matrix
    maximize_assignment(mat);
    fclose(fp);
    return 0;
}
