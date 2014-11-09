//
// Challenge name: Computer Terminal
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/108/
// Compile       : g++ -Wall -g -o ComputerTerminal ComputerTerminal.cpp
//

#include <stdio.h>
#include <ctype.h>
using namespace std;

#define MAX_LINE 2048
#define SIZE 10

enum Mode {
    OVERWRITE,
    INSERT,
};

struct Matrix {
    Mode m;
    int row, col;
    char mat[SIZE][SIZE];

    Matrix(): m(OVERWRITE), row(0), col(0) { clear(); }
    ~Matrix() {}

    void control(char c) {
        switch(c) {
        case 'c': clear();        break;
        case 'h': row = col = 0;  break;
        case 'b': col = 0;        break;
        case 'd': increment(row); break;
        case 'u': decrement(row); break;
        case 'l': decrement(col); break;
        case 'r': increment(col); break;
        case 'e': erase();        break;
        case 'i': m = INSERT;     break;
        case 'o': m = OVERWRITE;  break;
        default:  break;
        }
    }
    void put(char c) {
        if(m == INSERT)
            for(int i=SIZE-1;i>col;--i)
                mat[row][i] = mat[row][i-1];
        mat[row][col] = c;
        increment(col);
    }
    void changeRowCol(char r, char c) {
        row = char2digit(r);
        col = char2digit(c);
    }
    void print() const {
        for(int i=0;i<SIZE;++i) {
            for(int j=0;j<SIZE;++j) {
                printf("%c", mat[i][j]);
            }
            printf("\n");
        }
    }

private:
    void clear() {
        for(int i=0;i<SIZE;++i)
            for(int j=0;j<SIZE;++j)
                mat[i][j] = ' ';
    }
    void decrement(int& v) {
        --v;
        if(v < 0)   v = 0;
    }
    void increment(int& v) {
        ++v;
        if(v >= SIZE)   v = SIZE - 1;
    }
    void erase() {
        for(int i=col;i<SIZE;++i)   mat[row][i] = ' ';
    }
    int char2digit(char c) const {
        return (int)(c - '0');
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ComputerTerminal <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Matrix mm;
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        for(int i=0;i<MAX_LINE;++i) {
            char c = currentLine[i];
            if((c == '\n') || (c == '\r') || (c == '\0')) {
                break;
            }
            if(c == '^') {
                char next = currentLine[i+1];
                if(next == '^') {
                    mm.put('^');
                    ++i;
                    continue;
                }
                if(isdigit(next)) {
                    char next1 = currentLine[i+2];
                    mm.changeRowCol(next, next1);
                    i += 2;
                    continue;
                }
                mm.control(next);
                ++i;
                continue;
            }
            mm.put(c);
        }
    }
    fclose(fp);
    mm.print();
    return 0;
}
