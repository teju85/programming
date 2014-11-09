//
// Challenge name: City Blocks Flyover
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/133/
// Compile       : g++ -Wall -g -o CityBlocksFlyover CityBlocksFlyover.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;

struct Range {
    float s, e;
    bool isOverlapping(const Range& r) const {
        if((r.s > s) && (r.s < e)) {
            return true;
        }
        if((r.e > s) && (r.e < e)) {
            return true;
        }
        if((r.e == e) && (r.s != s)) {
            return true;
        }
        if((r.s == s) && (r.e != e)) {
            return true;
        }
        return false;
    }
    Range getRange(float slope) const {
        Range out = {slope * s,  slope * e};
        return out;
    }
};

void readRangeList(FILE* fp, vector<Range>& r) {
    int prev;
    if(fscanf(fp, "(%d", &prev) != 1) {
        if(fscanf(fp, ") (%d", &prev) != 1) {
            return;
        }
    }
    while(true) {
        int num;
        if(fscanf(fp, ",%d", &num) != 1) {
            break;
        }
        Range aa = {(float)prev, (float)num};
        r.push_back(aa);
        prev = num;
    }
    return;
}

void readLine(FILE* fp, vector<Range>& streets, vector<Range>& avenues) {
    readRangeList(fp, streets);
    readRangeList(fp, avenues);
}

float getSlope(vector<Range>& streets, vector<Range>& avenues) {
    int numS = (int)streets.size();
    int numA = (int)avenues.size();
    return (avenues[numA-1].e / streets[numS-1].e);
}

int numIntersectingInAvenue(Range& r, vector<Range>& avenues) {
    int num = 0;
    for(vector<Range>::iterator itr=avenues.begin();itr!=avenues.end();++itr) {
        if(itr->isOverlapping(r)) {
            ++num;
        }
        else if(r.isOverlapping(*itr)) {
            ++num;
        }
    }
    return num;
}

int numIntersecting(vector<Range>& streets, vector<Range>& avenues) {
    float slope = getSlope(streets, avenues);
    int num = 0;
    for(vector<Range>::iterator itr=streets.begin();itr!=streets.end();++itr) {
        Range tmp = itr->getRange(slope);
        num += numIntersectingInAvenue(tmp, avenues);
    }
    return num;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: CityBlocksFlyover <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<Range> streets;
        vector<Range> avenues;
        readLine(fp, streets, avenues);
        if(streets.empty() || avenues.empty()) {
            continue;
        }
        printf("%d\n", numIntersecting(streets, avenues));
    }
    fclose(fp);
    return 0;
}
