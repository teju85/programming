//
// Challenge name: TWENTY FORTY EIGHT
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/194/
// Compile       : g++ -Wall -g -o TwentyFortyEight TwentyFortyEight.cpp
//

#include <stdio.h>
#include <string.h>

#define MAX_TILE 16
#define MAX_STR 16

struct Tile {
    int dim;
    int mat[MAX_TILE][MAX_TILE];
    char dir[MAX_STR];
    bool isValid;

    Tile(FILE* fp) {
        isValid = false;
        if(fscanf(fp, "%s%d;", dir, &dim) != 2) {
            return;
        }
        for(int i=0;i<dim;++i) {
            for(int j=0;j<dim;++j) {
                if(fscanf(fp, "%d", &(mat[i][j])) != 1) {
                    return;
                }
            }
            fscanf(fp, "|");
        }
        isValid = true;
    }

    void apply() {
        if(!strcmp("RIGHT;", dir)) {
            moveRight();
        } else if(!strcmp("UP;", dir)) {
            moveUp();
        } else if(!strcmp("LEFT;", dir)) {
            moveLeft();
        } else if(!strcmp("DOWN;", dir)) {
            moveDown();
        }
    }

    void print() {
        for(int i=0;i<dim;++i) {
            for(int j=0;j<dim;++j) {
                if((i == 0) && (j == 0)) {
                    printf("%d", mat[i][j]);
                } else if((i != 0) && (j == 0)) {
                    printf("|%d", mat[i][j]);
                } else {
                    printf(" %d", mat[i][j]);
                }
            }
        }
        printf("\n");
    }

private:
    void moveRight() {
        for(int i=0;i<dim;++i) {
            // push all non-zeros to right-most end
            int firstNonZeroPos = dim;
            for(int j=dim-1;j>=0;--j) {
                if(mat[i][j] == 0) continue;
                mat[i][--firstNonZeroPos] = mat[i][j];
                if(firstNonZeroPos != j) {
                    mat[i][j] = 0;
                }
            }
            // merge same elements
            for(int j=dim-1;j>=1;--j) {
                if(mat[i][j] == mat[i][j-1]) {
                    mat[i][j] += mat[i][j-1];
                    mat[i][j-1] = 0;
                }
            }
            // again push all non-zeros to right-most end
            firstNonZeroPos = dim;
            for(int j=dim-1;j>=0;--j) {
                if(mat[i][j] == 0) continue;
                mat[i][--firstNonZeroPos] = mat[i][j];
                if(firstNonZeroPos != j) {
                    mat[i][j] = 0;
                }
            }
        }
    }

    void moveLeft() {
        for(int i=0;i<dim;++i) {
            // push all non-zeros to left-most end
            int firstNonZeroPos = -1;
            for(int j=0;j<dim;++j) {
                if(mat[i][j] == 0) continue;
                mat[i][++firstNonZeroPos] = mat[i][j];
                if(firstNonZeroPos != j) {
                    mat[i][j] = 0;
                }
            }
            // merge same elements
            for(int j=0;j<dim-1;++j) {
                if(mat[i][j] == mat[i][j+1]) {
                    mat[i][j] += mat[i][j+1];
                    mat[i][j+1] = 0;
                }
            }
            // again push all non-zeros to left-most end
            firstNonZeroPos = -1;
            for(int j=0;j<dim;++j) {
                if(mat[i][j] == 0) continue;
                mat[i][++firstNonZeroPos] = mat[i][j];
                if(firstNonZeroPos != j) {
                    mat[i][j] = 0;
                }
            }
        }
    }

    void moveUp() {
        for(int j=0;j<dim;++j) {
            // push all non-zeros to the top
            int firstNonZeroPos = -1;
            for(int i=0;i<dim;++i) {
                if(mat[i][j] == 0) continue;
                mat[++firstNonZeroPos][j] = mat[i][j];
                if(firstNonZeroPos != i) {
                    mat[i][j] = 0;
                }
            }
            // merge same elements
            for(int i=0;i<dim-1;++i) {
                if(mat[i][j] == mat[i+1][j]) {
                    mat[i][j] += mat[i+1][j];
                    mat[i+1][j] = 0;
                }
            }
            // again push all non-zeros to the top
            firstNonZeroPos = -1;
            for(int i=0;i<dim;++i) {
                if(mat[i][j] == 0) continue;
                mat[++firstNonZeroPos][j] = mat[i][j];
                if(firstNonZeroPos != i) {
                    mat[i][j] = 0;
                }
            }
        }
    }

    void moveDown() {
        for(int j=0;j<dim;++j) {
            // push all non-zeros to the bottom
            int firstNonZeroPos = dim;
            for(int i=dim-1;i>=0;--i) {
                if(mat[i][j] == 0) continue;
                mat[--firstNonZeroPos][j] = mat[i][j];
                if(firstNonZeroPos != i) {
                    mat[i][j] = 0;
                }
            }
            // merge same elements
            for(int i=dim-1;i>=1;--i) {
                if(mat[i][j] == mat[i-1][j]) {
                    mat[i][j] += mat[i-1][j];
                    mat[i-1][j] = 0;
                }
            }
            // again push all non-zeros to the bottom
            firstNonZeroPos = dim;
            for(int i=dim-1;i>=0;--i) {
                if(mat[i][j] == 0) continue;
                mat[--firstNonZeroPos][j] = mat[i][j];
                if(firstNonZeroPos != i) {
                    mat[i][j] = 0;
                }
            }
        }
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TwentyFortyEight <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Tile t(fp);
        if(!t.isValid) {
            continue;
        }
        t.apply();
        t.print();
    }
    fclose(fp);
    return 0;
}
