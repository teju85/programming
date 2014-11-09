//
// Challenge name: Find a Square
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/101/
// Compile       : g++ -Wall -g -o FindSquare FindSquare.cpp
//

#include <stdio.h>
#define ABSDIFF(a, b)   (a < b)? (b - a) : (a - b)

struct Point {
    int x, y;
    void swapWith(Point& a) {
        int tmp;
        tmp = x;
        x = a.x;
        a.x = tmp;
        tmp = y;
        y = a.y;
        a.y = tmp;
    }
};
Point points[4];

int dist(const Point& a, const Point& b) {
    int d1 = (a.x - b.x);
    int d2 = (a.y - b.y);
    return ((d1 * d1) + (d2 * d2));
}

bool isCurrentComboSquare() {
    int side1 = dist(points[0], points[1]);
    int side2 = dist(points[1], points[2]);
    if(side1 != side2) {
        return false;
    }
    int side3 = dist(points[2], points[3]);
    if(side2 != side3) {
        return false;
    }
    int side4 = dist(points[3], points[0]);
    if(side3 != side4) {
        return false;
    }
    int diag1 = dist(points[0], points[2]);
    int diag2 = dist(points[1], points[3]);
    if(diag1 != diag2) {
        return false;
    }
    return true;
}

bool isSquare() {
    //  d - c
    //  |   |
    //  a - b
    if(isCurrentComboSquare()) return true;
    //  c - d
    //  |   |
    //  a - b
    points[2].swapWith(points[3]);
    if(isCurrentComboSquare()) return true;
    //  b - d
    //  |   |
    //  a - c
    points[1].swapWith(points[3]);
    if(isCurrentComboSquare()) return true;
    //  d - b
    //  |   |
    //  a - c
    points[2].swapWith(points[3]);
    if(isCurrentComboSquare()) return true;
    //  c - b
    //  |   |
    //  a - d
    points[1].swapWith(points[3]);
    if(isCurrentComboSquare()) return true;
    //  b - c
    //  |   |
    //  a - d
    points[2].swapWith(points[3]);
    if(isCurrentComboSquare()) return true;
    return false;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: FindSquare <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int len = fscanf(fp, "(%d,%d), (%d,%d), (%d,%d), (%d,%d)\n",
                         &(points[0].x), &(points[0].y),
                         &(points[1].x), &(points[1].y),
                         &(points[2].x), &(points[2].y),
                         &(points[3].x), &(points[3].y));
        if(len != 8) {
            continue;
        }
        printf("%s\n", isSquare()? "true" : "false");
    }
    fclose(fp);
    return 0;
}
