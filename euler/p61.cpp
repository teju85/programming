//
// Challenge name: Problem 61
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=61
// Compile       : g++ -Wall -g -o p61 p61.cpp
// Run           : ./p61
//

#include <stdio.h>
#include <map>
#include <vector>
typedef std::map<int, int> Nmap;
typedef std::vector<int> NmapIdx;
typedef std::vector<Nmap> Maps;
#define LIMIT 500

Nmap triangle;
Nmap square;
Nmap pentagonal;
Nmap hexagonal;
Nmap heptagonal;
Nmap octagonal;

NmapIdx idx;
Maps maps;

void initializeNmap() {
#define ADD_ELE(n, val, nmap) \
    if((val >= 1000) && (val <= 9999))   nmap[val] = n

    for(int n=1;n<=LIMIT;++n) {
        int val;
        // triangle
        val = (n * (n + 1)) >> 1;
        ADD_ELE(n, val, triangle);
        // square
        val = n * n;
        ADD_ELE(n, val, square);
        // pentagonal
        val = (n * ((3 * n) - 1)) >> 1;
        ADD_ELE(n, val, pentagonal);
        // hexagonal
        val = n * ((n << 1) - 1);
        ADD_ELE(n, val, hexagonal);
        // heptagonal
        val = (n * ((5 * n) - 3)) >> 1;
        ADD_ELE(n, val, heptagonal);
        // octagonal
        val = n * ((3 * n) - 2);
        ADD_ELE(n, val, octagonal);
    }

    maps.push_back(triangle);
    maps.push_back(square);
    maps.push_back(pentagonal);
    maps.push_back(hexagonal);
    maps.push_back(heptagonal);
    maps.push_back(octagonal);

#undef ADD_ELE
}

void initializeIdx() {
    for(int i=0;i<5;++i) {
        idx[i] = 0;
    }
    idx[5] = 1;
}

int findCyclicLower(int low, Nmap& nmap) {
    for(int val=low+1000;val<10000;val+=100) {
        if(nmap.find(val) != nmap.end()) {
            return val;
        }
    }
    return -1;
}

int findCyclicHigher(int high, Nmap& nmap) {
    int lim = high + 100;
    for(int val=high;val<lim;++val) {
        if(nmap.find(val) != nmap.end()) {
            return val;
        }
    }
    return -1;
}

void findUniqueCombo() {
    return;
}

int main(int argc, char** argv) {
    initializeNmap();
    findUniqueCombo();
    return 0;
}
