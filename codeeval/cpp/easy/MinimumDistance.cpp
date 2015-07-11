//
// Challenge name: Minimum Distance
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/189/
// Compile       : g++ -Wall -g -o MinimumDistance MinimumDistance.cpp
//

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int minimumDistance(int N, vector<int>& friends) {
    sort(friends.begin(), friends.end());
    int median;
    if(N & 0x1) {
        int mid = (N + 1) >> 1;
        median = friends[mid-1];
    }
    else {
        int mid = N >> 1;
        median = (friends[mid] + friends[mid-1]) >> 1;
    }
    int diff = 0;
    for(vector<int>::iterator i=friends.begin();i!=friends.end();++i) {
        int a = *i - median;
        if(a < 0) {
            a = -a;
        }
        diff += a;
    }
    return diff;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MinimumDistance <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int N = -1;
        if(fscanf(fp, "%d", &N) != 1) {
            continue;
        }
        vector<int> friends;
        for(int i=0;i<N;++i) {
            int val;
            fscanf(fp, "%d", &val);
            friends.push_back(val);
        }
        printf("%d\n", minimumDistance(N, friends));
    }
    fclose(fp);
    return 0;
}
