//
// Challenge name: Interrupted Bubble Sort
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/158/
// Compile       : g++ -Wall -g -o InterruptedBubbleSort InterruptedBubbleSort.cpp
//

#include <stdio.h>
#include <vector>

using namespace std;

int readVector(FILE* fp, vector<int>& arr) {
    int numIter = 0;
    while(!feof(fp)) {
        int num = 0;
        if(fscanf(fp, " | %d", &num) == 1) {
            numIter = num;
            break;
        }
        if(fscanf(fp, "%d", &num) == 1) {
            arr.push_back(num);
        }
    }
    return numIter;
}

void ibs(vector<int>& vec, int numIter) {
    int size = ((int) vec.size()) - 1;
    while(numIter > 0) {
        for(int i=0;i<size;++i) {
            if(vec[i] > vec[i+1]) {
                int t = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = t;
            }
        }
        --numIter;
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: InterruptedBubbleSort <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        vector<int> vec;
        int numIter = readVector(fp, vec);
        if(numIter < 0) {
            continue;
        }
        int size = (int)vec.size();
        if(size <= 0) {
            continue;
        }
        if(numIter > size) {
            numIter = size;
        }
        ibs(vec, numIter);
        vector<int>::const_iterator itr = vec.begin();
        printf("%d", *itr);
        for(++itr;itr!=vec.end();++itr) {
            printf(" %d", *itr);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
