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
    Matrix(const Matrix& mat, Location& l1, Location& l2);
    ~Matrix();
    Locations min_locations() const;
    Locations max_locations() const;
    Locations max_locations_row(int r) const;
    Locations max_locations_col(int c) const;
};
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
Locations Matrix::min_locations() const {
    Locations locs;
    if((R <= 0) || (C <= 0)) {
        return locs;
    }
    int min = 0x7fffffff;
    for(int i=0;i<R;++i) {
        for(int j=0;j<C;++j) {
            if(min > data[i][j]) {
                min = data[i][j];
            }
        }
    }
    for(int i=0;i<R;++i) {
        for(int j=0;j<C;++j) {
            if(min == data[i][j]) {
                Location l = { i, j };
                locs.push_back(l);
            }
        }
    }
    return locs;
}
Locations Matrix::max_locations() const {
    Locations locs;
    if((R <= 0) || (C <= 0)) {
        return locs;
    }
    int max = 0x80000000;
    for(int i=0;i<R;++i) {
        for(int j=0;j<C;++j) {
            if(max < data[i][j]) {
                max = data[i][j];
            }
        }
    }
    for(int i=0;i<R;++i) {
        for(int j=0;j<C;++j) {
            if(max == data[i][j]) {
                Location l = { i, j };
                locs.push_back(l);
            }
        }
    }
    return locs;
}
Locations Matrix::max_locations_row(int r) const {
    Locations locs;
    if((R <= 0) || (C <= 0)) {
        return locs;
    }
    int max = 0xffffffff;
    for(int i=0;i<C;++i) {
        if(max < data[r][i]) {
            max = data[r][i];
        }
    }
    for(int i=0;i<C;++i) {
        if(max == data[r][i]) {
            Location l = { r, i };
            locs.push_back(l);
        }
    }
    return locs;
}
Locations Matrix::max_locations_col(int c) const {
    Locations locs;
    if((R <= 0) || (C <= 0)) {
        return locs;
    }
    int max = 0xffffffff;
    for(int i=0;i<R;++i) {
        if(max < data[i][c]) {
            max = data[i][c];
        }
    }
    for(int i=0;i<C;++i) {
        if(max == data[i][c]) {
            Location l = { i, c };
            locs.push_back(l);
        }
    }
    return locs;
}
////// matrix of integers //////



// using min pivot
int find_matrix_sum_method1(Matrix& mat);
// using max pivot
int find_matrix_sum_method2(Matrix& mat);

int find_matrix_sum_method1(Matrix& mat) {
    if((mat.R <= 0) || (mat.C <= 0)) {
        return 0;
    }
    if((mat.R == 1) && (mat.C == 1)) {
        return mat.data[0][0];
    }
    Locations locs = mat.min_locations();
    if(locs.size() <= 0) {
        return 0;
    }
    int max = 0;
    for(Litr itr=locs.begin();itr!=locs.end();++itr) {
        Locations l_r = mat.max_locations_row(itr->r);
        Locations l_c = mat.max_locations_col(itr->c);
        for(Litr itr1=l_r.begin();itr1!=l_r.end();++itr1) {
            int s = mat.data[itr1->r][itr1->c];
            for(Litr itr2=l_c.begin();itr2!=l_c.end();++itr2) {
                //printf("M1: d=(%d,%d) mi=(%d,%d) mar=(%d,%d) mac=(%d,%d)\n",
                //       mat.R, mat.C, itr->r, itr->c, itr1->r, itr1->c,
                //       itr2->r, itr2->c);
                Matrix mat1(mat, *itr1, *itr2);
                int s11 = s + mat.data[itr2->r][itr2->c];
                int s1 = s11 + find_matrix_sum_method1(mat1);
                int s2 = s11 + find_matrix_sum_method2(mat1);
                if(s1 > max) {
                    max = s1;
                }
                if(s2 > max) {
                    max = s2;
                }
            }
        }
    }
    return max;
}

int find_matrix_sum_method2(Matrix& mat) {
    if((mat.R <= 0) || (mat.C <= 0)) {
        return 0;
    }
    if((mat.R == 1) && (mat.C == 1)) {
        return mat.data[0][0];
    }
    Locations locs = mat.max_locations();
    if(locs.size() <= 0) {
        return 0;
    }
    int num = mat.data[locs[0].r][locs[0].c];
    int max = 0;
    for(Litr itr=locs.begin();itr!=locs.end();++itr) {
        //printf("M2: d=(%d,%d) ma=(%d,%d)\n", mat.R, mat.C, itr->r, itr->c);
        Matrix mat1(mat, *itr, *itr);
        int s1 = find_matrix_sum_method1(mat1);
        int s2 = find_matrix_sum_method2(mat1);
        if(s1 > max) {
            max = s1;
        }
        if(s2 > max) {
            max = s2;
        }
    }
    return (num + max);
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
    int num1 = find_matrix_sum_method1(mat);
    int num2 = find_matrix_sum_method2(mat);
    printf("%d\n", (num1 < num2)? num2 : num1);
    fclose(fp);
    return 0;
}
