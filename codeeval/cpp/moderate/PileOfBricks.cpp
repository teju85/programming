//
// Challenge name: A Pile Of Bricks
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/117/
// Compile       : g++ -Wall -g -o PileOfBricks PileOfBricks.cpp
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define ABS(a)  (a < 0)? -a : a

struct Hole {
    int w;
    int h;
    bool canPassThrough(int w1, int h1) const {
        if((w1 <= w) && (h1 <= h)) {
            return true;
        }
        if((h1 <= w) && (w1 <= h)) {
            return true;
        }
        return false;
    }
    bool read(FILE* fp) {
        int x1, y1, x2, y2;
        if(fscanf(fp, "[%d,%d] [%d,%d]", &x1, &y1, &x2, &y2) != 4) {
            return false;
        }
        w = x1 - x2;  w = ABS(w);
        h = y1 - y2;  h = ABS(h);
        return true;
    }
};

struct Brick {
    int x1, x2;
    int y1, y2;
    int z1, z2;
    int idx;
    bool read(FILE* fp) {
        if(fscanf(fp,"(%d [%d,%d,%d] [%d,%d,%d])",&idx,&x1,&y1,&z1,&x2,&y2,&z2) != 7) {
            return false;
        }
        return true;
    }
    bool canPassThrough(const Hole& h) const {
        return (canPassThrough(h, x1, y1, x2, y2) ||
                canPassThrough(h, y1, z1, y2, z2) ||
                canPassThrough(h, z1, x1, z2, x2));
    }
private:
    bool canPassThrough(const Hole& hole, int x1, int y1, int x2, int y2) const {
        int w = x1 - x2;  w = ABS(w);
        int h = y1 - y2;  h = ABS(h);
        return hole.canPassThrough(w, h);
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PileOfBricks <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<int> idxs;
        Hole hole;
        if(!hole.read(fp)) {
            break;
        }
        fscanf(fp, "|");
        while(true) {
            Brick b;
            if(!b.read(fp)) {
                break;
            }
            fscanf(fp, ";");
            if(b.canPassThrough(hole)) {
                idxs.push_back(b.idx);
            }
        }
        fscanf(fp, "\n");
        if(idxs.empty()) {
            printf("-\n");
            continue;
        }
        sort(idxs.begin(), idxs.end());
        vector<int>::const_iterator itr = idxs.begin();
        printf("%d", *itr);
        for(++itr;itr!=idxs.end();++itr) {
            printf(",%d", *itr);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
