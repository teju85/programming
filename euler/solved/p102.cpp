//
// Challenge name: Problem 102
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=102
// Compile       : g++ -Wall -g -o p102 p102.cpp
// Run           : ./p102 p102.txt
//

#include <stdio.h>

struct Point {
    float x;
    float y;
};

struct Triangle {
    Point A;
    Point B;
    Point C;
};


Point add(const Point& a, const Point& b) {
    Point c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Point subtract(const Point& a, const Point& b) {
    Point c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

Point scalar_mult(const Point& a, float m) {
    Point c;
    c.x = m * a.x;
    c.y = m * a.y;
    return c;
}

float dot_mult(const Point& a, const Point& b) {
    return ((a.x * b.x) + (a.y * b.y));
}

// barycentric-test
// REF: http://www.blackpawn.com/texts/pointinpoly/default.html
bool is_inside(const Triangle& t, const Point& p) {
    Point v0 = subtract(t.C, t.A);
    Point v1 = subtract(t.B, t.A);
    Point v2 = subtract(p, t.A);
    float v20 = dot_mult(v2, v0);
    float v21 = dot_mult(v2, v1);
    float v00 = dot_mult(v0, v0);
    float v11 = dot_mult(v1, v1);
    float v01 = dot_mult(v0, v1);
    float v10 = v01;
    float del = (v00 * v11) - (v01 * v10);
    float u = ((v11 * v20) - (v10 * v21)) / del;
    float v = ((v00 * v21) - (v01 * v20)) / del;
    if((u < 0.0f) || (v < 0.0f) || ((u + v) > 1.0f)) {
        return false;
    }
    return true;
}

void read_triangle(Triangle& t, FILE* fp) {
    fscanf(fp, "%f,%f,%f,%f,%f,%f", &(t.A.x), &(t.A.y),
           &(t.B.x), &(t.B.y), &(t.C.x), &(t.C.y));
}



int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p102 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    int num;
    int contain = 0;
    Triangle t;
    Point p = {0.0f, 0.0f};
    fscanf(fp, "%d", &num);
    for(int i=0;i<num;++i) {
        read_triangle(t, fp);
        if(is_inside(t, p)) {
            ++contain;
        }
    }
    fclose(fp);
    printf("%d\n", contain);
    return 0;
}
