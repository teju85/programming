//
// Challenge name: Bats Challenge
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/146/
// Compile       : g++ -Wall -g -o BatsChallenge BatsChallenge.cpp
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;


struct HangingWire {
    int length;
    int batDistance;
    vector<int> batsPos;

    bool read(FILE* fp) {
        length = batDistance = -1;
        int numBats = 0;
        fscanf(fp, "%d%d%d", &length, &batDistance, &numBats);
        if(length <= 0) {
            return false;
        }
        for(;numBats>0;--numBats) {
            int tmp;
            fscanf(fp, "%d", &tmp);
            batsPos.push_back(tmp);
        }
        sort(batsPos.begin(), batsPos.end());
        return true;
    }

    int maxMoreBats() const {
        int num = 0;
        int size = (int)batsPos.size();
        int prev = DIST_FROM_WALL;
        for(int i=0;i<size;++i) {
            int curr = batsPos[i];
            num += numBatsToFit(prev, curr);
            prev = curr;
        }
        num += numBatsToFit(prev, length - DIST_FROM_WALL + batDistance);
        num -= size; // you would have counted these as well
        if(num < 0) {
            num = 0;
        }
        return num;
    }

private:
    int numBatsToFit(int start, int end) const {
        int num = 0;
        for(;start<end;start+=batDistance) {
            if((end - start) < batDistance) {
                break;
            }
            ++num;
        }
        return num;
    }

    static const int DIST_FROM_WALL = 6;
};


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BatsChallenge <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        HangingWire hw;
        if(!hw.read(fp)) {
            continue;
        }
        printf("%d\n", hw.maxMoreBats());
    }
    fclose(fp);
    return 0;
}
