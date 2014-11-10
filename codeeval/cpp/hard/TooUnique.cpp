//
// Challenge name: Too Unique
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/162/
// Compile       : g++ -Wall -g -o TooUnique TooUnique.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
#define MAX_COLS  128
#define NUM_CHARS 26

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

struct histogram {
    histogram() {}
    ~histogram() {}
    histogram(const histogram& h) {
        for(int i=0;i<NUM_CHARS;++i) {
            hist[i] = h.hist[i];
        }
    }
    void init() {
        for(int i=0;i<NUM_CHARS;++i) {
            hist[i] = 0;
        }
    }
    void evaluate(const vector<string>& matrix, int startX, int startY,
                  int sizeX, int sizeY) {
        init();
        int x = startX + sizeX;
        int y = startY + sizeY;
        for(int i=startX;i<x;++i) {
            for(int j=startY;j<y;++j) {
                int p = (int) (matrix[i][j] - 'a');
                hist[p]++;
            }
        }
    }
    bool isUnique() const {
        for(int i=0;i<NUM_CHARS;++i) {
            if(hist[i] > 1) {
                return false;
            }
        }
        return true;
    }
    int hist[NUM_CHARS];
};

bool divisors[NUM_CHARS+1][NUM_CHARS+1];
void allDivisors() {
    for(int j=0;j<=NUM_CHARS;++j) {
        divisors[0][j] = false;
    }
    for(int i=NUM_CHARS;i>=1;--i) {
        divisors[i][0] = false;
        for(int j=1;j<=NUM_CHARS;++j) {
            divisors[i][j] = ((i % j) == 0);
        }
    }
}

struct Block {
    int x, y;
    int row, col;
    Block(int xx, int yy, int r, int c): x(xx), y(yy), row(r), col(c) {}
    ~Block() {}
    Block(const Block& b): x(b.x), y(b.y), row(b.row), col(b.col) {}
    void mask(vector<string>& matrix) const {
        int ex = x + row;
        int ey = y + col;
        for(int i=x;i<ex;++i) {
            for(int j=y;j<ey;++j) {
                matrix[i][j] = '*';
            }
        }
    }
};

void checkForUniq(const vector<string>& matrix, histogram& hist, vector<Block>& uniqs,
                  int rowSize, int colSize, int numRows, int numCols) {
    int x = numRows - rowSize + 1;
    int y = numCols - colSize + 1;
    for(int i=0;i<x;++i) {
        for(int j=0;j<y;++j) {
            hist.init();
            hist.evaluate(matrix, i, j, rowSize, colSize);
            if(hist.isUnique()) {
                Block blk(i, j, rowSize, colSize);
                uniqs.push_back(blk);
            }
        }
    }
}

void maxUniqSize(vector<string>& matrix) {
    histogram hist;
    vector<Block> uniqs;
    allDivisors();
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();
    for(int i=NUM_CHARS;i>1;--i) {
        for(int j=0;j<=NUM_CHARS;++j) {
            if(!divisors[i][j]) {
                continue;
            }
            int sizeX = j;
            int sizeY = i / j;
            if((sizeX > rows) || (sizeY > cols)) {
                continue;
            }
            checkForUniq(matrix, hist, uniqs, sizeX, sizeY, rows, cols);
        }
        if(uniqs.size() > 0) {
            break;
        }
    }
    for(vector<Block>::iterator itr=uniqs.begin();itr!=uniqs.end();++itr) {
        itr->mask(matrix);
    }
}

void printMatrix(const vector<string>& matrix) {
    for(vector<string>::const_iterator i=matrix.begin();i!=matrix.end();++i) {
        printf("%s\n", i->c_str());
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TooUnique <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    vector<string> matrix;
    while(!feof(fp)) {
        char curr[MAX_COLS];
        curr[0] = '\0';
        fgets(curr, MAX_COLS, fp);
        if(curr[0] == '\0') {
            continue;
        }
        stringLen(curr, MAX_COLS);
        matrix.push_back(curr);
    }
    fclose(fp);
    maxUniqSize(matrix);
    printMatrix(matrix);
    return 0;
}
