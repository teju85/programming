//
// Challenge name: Point in Circle
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/98/
// Compile       : g++ -Wall -g -o PointInCircle PointInCircle.cpp
//

#include <stdio.h>

struct Point {
    float x, y;
};

struct Circle {
    Point center;
    float radius;
    bool insideCircle(const Point& p) {
        float x = (center.x - p.x);
        float y = (center.y - p.y);
        return (((x * x) + (y * y)) < (radius * radius));
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PointInCircle <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Circle c;
        Point p;
        int len = fscanf(fp, "Center: (%f, %f); Radius: %f; Point: (%f, %f)\n",
                         &(c.center.x), &(c.center.y), &(c.radius), &(p.x), &(p.y));
        if(len != 5) {
            continue;
        }
        printf("%s\n", c.insideCircle(p)? "true" : "false");
    }
    fclose(fp);
    return 0;
}
