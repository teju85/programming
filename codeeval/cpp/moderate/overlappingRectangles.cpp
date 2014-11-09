//
// Challenge name: Overlapping Rectangles
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/70/
// Compile       : g++ -Wall -g -o overlappingRectangles overlappingRectangles.cpp
//

#include <stdio.h>

struct Rect {
    int ulx; // upper left x
    int uly; // upper left y
    int lrx; // lower right x
    int lry; // lower right y
    bool isOverlapping(const Rect& r) {
        bool onX = (((r.ulx>=ulx)&&(r.ulx<=lrx)) || ((r.lrx>=ulx)&&(r.lrx<=lrx)));
        bool onY = (((r.uly<=uly)&&(r.uly>=lry)) || ((r.lry<=uly)&&(r.lry>=lry)));
        return (onX && onY);
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: overlappingRectangles <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Rect a, b;
    while(!feof(fp)) {
        int num = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d",
                         &(a.ulx), &(a.uly), &(a.lrx), &(a.lry),
                         &(b.ulx), &(b.uly), &(b.lrx), &(b.lry));
        if(num != 8) {
            continue;
        }
        printf("%s\n", a.isOverlapping(b)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
