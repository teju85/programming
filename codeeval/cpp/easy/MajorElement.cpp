//
// Challenge name: Major Element
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/132/
// Compile       : g++ -Wall -g -o MajorElement MajorElement.cpp
//

#include <stdio.h>
#include <map>
using namespace std;

struct Major {
    map<int, int> seq;
    int L;
    Major(): seq(), L(0) {}
    void addElements(FILE* fp) {
        while(addElement(fp));
    }
    bool addElement(FILE* fp) {
        int e = -1;
        if(feof(fp)) {
            return false;
        }
        if(fscanf(fp, "%d", &e) != 1) {
            return false;
        }
        add(e);
        if(fgetc(fp) == ',') {
            return true;
        }
        return false;
    }
    void add(int e) {
        if(seq.find(e) != seq.end()) {
            seq[e]++;
        }
        else {
            seq[e] = 1;
        }
        ++L;
    }
    int findMajor() const {
        int L2 = (L >> 1);
        for(map<int,int>::const_iterator itr=seq.begin();itr!=seq.end();++itr) {
            if(itr->second > L2) {
                return itr->first;
            }
        }
        return -1;
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MajorElement <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Major m;
        m.addElements(fp);
        if(m.L <= 0) {
            continue;
        }
        int me = m.findMajor();
        if(me == -1) {
            printf("None\n");
            continue;
        }
        printf("%d\n", me);
    }
    fclose(fp);
    return 0;
}
