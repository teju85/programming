//
// Challenge name: Skyscrapers
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/120/
// Compile       : g++ -Wall -g -o Skyscrapers Skyscrapers.cpp
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Building {
    int start, height, end;
    int read(FILE* fp) {
        if(fscanf(fp, "(%d,%d,%d); ", &start, &height, &end) == 3) {
            return 1;
        }
        if(fscanf(fp, "(%d,%d,%d)", &start, &height, &end) == 3) {
            return 2;
        }
        return 0;
    }
    bool intersect(int p) const {
        if((start <= p) && (p <= end)) {
            return true;
        }
        return false;
    }
};

bool BuildingSorter(const Building& b1, const Building& b2) {
    if(b1.start == b2.start) {
        return (b1.height > b2.height);
    }
    return (b1.start < b2.start);
}

struct Position {
    int x;
    const Building* p;
    bool isStart() const {
        return (x == p->start);
    }
};

bool PositionSorter(const Position& p1, const Position& p2) {
    if(p1.x == p2.x) {
        return (p1.p->height > p2.p->height);
    }
    return (p1.x < p2.x);
}

int findPos(const vector<int>& outx, int p) {
    int num = (int)outx.size();
    for(int i=num-1;i>=0;--i) {
        if(outx[i] < p) {
            return i;
        }
    }
    return -1;
}

void putNewBuilding(vector<int>& outx, vector<int>& outh, const Building& b) {
    outx.push_back(b.start);
    outx.push_back(b.end);
    outh.push_back(b.height);
    outh.push_back(0);
}

void mergeOutline(vector<int>& outx, vector<int>& outh, const Building& b) {
    int num = (int) outx.size();
    if(num <= 0) {
        putNewBuilding(outx, outh, b);
        return;
    }
    int pos = findPos(b.start);
    // no intersection
    if(pos == (num - 1)) {
        putNewBuilding(outx, outh, b);
        return;
    }
    // start of new block is taller
    if(b.height > outh[pos]) {
        ++pos;
        outx.insert(outx.begin()+pos, b.start);
        outh.insert(outh.begin()+pos, b.height);
        pos = findPos(b.end) + 1;
    }
    // start of new block is shorter
    else {
        pos = findPos(b.end);
        // goes out of the current last position
        if(pos == (num - 1)) {
            outx.push_back(b.end);
            outh.insert(outh.begin()+pos, b.height);
            return;
        }
    }
}

void drawOutline(vector<Building>& b) {
    vector<int> outx, outh;
    sort(b.begin(), b.end(), BuildingSorter);
    for(vector<Building>::const_iterator i=b.begin();i!=b.end();++i) {
        mergeOutline(outx, outh, *i);
        break;
    }
    int num = (int) outx.size();
    bool first = true;
    for(int i=0;i<num;++i) {
        if(first) {
            printf("%d %d", outx[i], outh[i]);
        }
        else {
            printf(" %d %d", outx[i], outh[i]);
        }
        first = false;
    }
    printf("\n");
    /*
    vector<Position> pos;
    for(vector<Building>::const_iterator itr=b.begin();itr!=b.end();++itr) {
        Position p1 = {itr->start, &(*itr)};
        Position p2 = {itr->end,   &(*itr)};
        pos.push_back(p1);
        pos.push_back(p2);
    }
    sort(pos.begin(), pos.end(), PositionSorter);
    vector<int> outline;
    int prevX = -1;
    bool prevStart = false;
    int prevH = -1;
    for(vector<Position>::const_iterator i=pos.begin();i!=pos.end();++i) {
        if((prevX == i->x) && (prevStart == i->isStart())) {
            continue;
        }
        prevX = i->x;
        prevStart = i->isStart();
        outline.push_back(i->x);
        outline.push_back(i->p->height);
        prevH = i->p->height;
    }
    */
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: Skyscrapers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<Building> builds;
        while(true) {
            Building b;
            int status = b.read(fp);
            if(status == 0) {
                fscanf(fp, "\n");
                break;
            }
            builds.push_back(b);
        }
        if(builds.size() <= 0) {
            continue;
        }
        drawOutline(builds);
    }
    fclose(fp);
    return 0;
}
