//
// Challenge name: Package Problem
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/114/
// Compile       : g++ -Wall -g -o PackageProblem PackageProblem.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;

struct Item {
    int index;
    float weight;
    float cost;
    bool populate(FILE* fp) {
        if(fscanf(fp, " (%d,%f,$%f)", &index, &weight, &cost) != 3) {
            return false;
        }
        return true;
    }
    void print() const {
        printf("idx=%2d weight=%.2f cost=%.2f\n", index, weight, cost);
    }
};

struct Package {
    float totalWeight;
    vector<Item> things;
    vector<int> indices;
    bool isEmpty() const {
        return things.empty();
    }
    void populate(FILE* fp) {
        if(fscanf(fp, "%f :", &totalWeight) == 0) {
            return;
        }
        while(true) {
            Item i;
            if(!i.populate(fp)) {
                break;
            }
            things.push_back(i);
        }
        fscanf(fp, "\n");
    }
    void sortOnCost() {
        int s = (int)things.size();
        for(int i=0;i<s;++i) {
            for(int j=i+1;j<s;++j) {
                if(things[i].cost > things[j].cost) {
                    continue;
                }
                Item t = things[i];
                things[i] = things[j];
                things[j] = t;
            }
        }
    }
    void evaluateSelection() {
        sortOnCost();
        for(vector<Item>::const_iterator itr=things.begin();itr!=things.end();++itr) {
            itr->print();
        }
    }
    void printSelection() const {
        if(indices.size() <= 0) {
            printf("-\n");
            return;
        }
        bool first = true;
        for(vector<int>::const_iterator itr=indices.begin();itr!=indices.end();++itr) {
            if(first) {
                printf("%d", *itr);
                first = false;
            }
            else {
                printf(",%d\n", *itr);
            }
        }
        printf("\n");
    }
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PackageProblem <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        Package pkg;
        pkg.populate(fp);
        if(pkg.isEmpty()) {
            continue;
        }
        pkg.evaluateSelection();
        pkg.printSelection();
    }
    fclose(fp);
    return 0;
}
