//
// Challenge name: Bay Area Bridge
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/109/
// Compile       : g++ -Wall -g -o BayAreaBridge BayAreaBridge.cpp
//

#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

struct LineSegment {
    float x1, y1;
    float x2, y2;
    int idx;
    bool read(FILE* fp) {
        if(fscanf(fp, "%d: ([%f,%f], [%f,%f])", &idx, &x1, &y1, &x2, &y2) == 5) {
            fscanf(fp, "\n");
            return true;
        }
        if(fscanf(fp, "%d: ([%f, %f], [%f, %f])", &idx, &x1, &y1, &x2, &y2) == 5) {
            fscanf(fp, "\n");
            return true;
        }
        return false;
    }
    bool onSegment(float x, float y) const {
        return (withinRange(x, x1, x2) && withinRange(y, y1, y2));
    }
private:
    bool withinRange(float a, float a1, float a2) const {
        if(a2 < a1) {
            float t = a2;
            a2 = a1;
            a1 = t;
        }
        return ((a >= a1) && (a <= a2));
    }
};

struct Line {
    float m, c;  // y = mx + c
    void calculate(const LineSegment& seg) {
        m = (seg.y1 - seg.y2) / (seg.x1 - seg.x2);
        c = seg.y1 - (m * seg.x1);
    }
    void intersect(const Line& line, float& x, float& y) const {
        x = (line.c - c) / (m - line.m);
        y = (m * x) + c;
    }
};

struct Bridge {
    Line line;
    LineSegment seg;
    int numCrossings;
    bool intersect(const Bridge& b) const {
        float x, y;
        line.intersect(b.line, x, y);
        return seg.onSegment(x, y);
    }
};

void populateAdjacency(const vector<Bridge>& b, bool** a) {
    int n = (int)b.size();
    for(int i=0;i<n;++i) {
        for(int j=i+1;j<n;++j) {
            a[i][j] = a[j][i] = !(b[i].intersect(b[j]));
        }
    }
}

int minConnectedVertex(bool** a, int n, const set<int>& added) {
    int min = n + 1;
    int ver = -1;
    for(int i=0;i<n;++i) {
        if(added.find(i) == added.end()) {
            continue;
        }
        int sum = 0;
        for(int j=0;j<n;++j) {
            if(added.find(j) == added.end()) {
                continue;
            }
            sum += a[i][j];
        }
        if(sum < min) {
            min = sum;
            ver = i;
        }
    }
    return ver;
}

bool isClique(bool** a, int n, const set<int>& cliq) {
    int expected = (int)cliq.size();
    expected = expected * (expected - 1);
    int numEdges = 0;
    for(set<int>::const_iterator itr=cliq.begin();itr!=cliq.end();++itr) {
        for(int i=0;i<n;++i) {
            if(cliq.find(i) == cliq.end()) {
                continue;
            }
            numEdges += a[*itr][i];
        }
    }
    return (numEdges == expected);
}

set<int> findMaximumClique(bool** a, int n) {
    set<int> used;
    for(int i=0;i<n;++i) {
        used.insert(i);
    }
    while(!isClique(a, n, used)  &&  (used.size() > 1)) {
        int m = minConnectedVertex(a, n, used);
        used.erase(m);
    }
    return used;
}

void printBridges(const set<int>& c, vector<Bridge>& b) {
    vector<int> cliq;
    for(set<int>::const_iterator itr=c.begin();itr!=c.end();++itr) {
        cliq.push_back(*itr);
    }
    int n = (int)cliq.size();
    for(int i=0;i<n;++i) {
        cliq[i] = b[cliq[i]].seg.idx;
    }
    for(int i=0;i<n;++i) {
        for(int j=i+1;j<n;++j) {
            if(cliq[i] > cliq[j]) {
                int t = cliq[i];
                cliq[i] = cliq[j];
                cliq[j] = t;
            }
        }
        printf("%d\n", cliq[i]);
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BayAreaBridge <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    vector<Bridge> bridges;
    while(!feof(fp)) {
        Bridge b;
        if(!b.seg.read(fp)) {
            break;
        }
        b.numCrossings = 0;
        b.line.calculate(b.seg);
        bridges.push_back(b);
    }
    fclose(fp);
    int numBs = (int) bridges.size();
    bool** adjacency = new bool*[numBs];
    for(int i=0;i<numBs;++i) {
        adjacency[i] = new bool[numBs];
        for(int j=0;j<numBs;++j) {
            adjacency[i][j] = 0;
        }
    }
    populateAdjacency(bridges, adjacency);
    set<int> cliq = findMaximumClique(adjacency, numBs);
    printBridges(cliq, bridges);
    for(int i=0;i<numBs;++i) {
        delete [] adjacency[i];
    }
    delete [] adjacency;
    return 0;
}
