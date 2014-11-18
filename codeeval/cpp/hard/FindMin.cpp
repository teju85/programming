//
// Challenge name: Find Min
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/85/
// Compile       : g++ -Wall -g -o FindMin FindMin.cpp
//

#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
#define INT long long int

void addElement(vector<INT>& arr, map<INT,INT>& sorted, INT elem) {
    arr.push_back(elem);
    if(sorted.find(elem) != sorted.end()) {
        sorted[elem] += 1;
    }
    else {
        sorted[elem] = 1;
    }
}

void deleteElement(vector<INT>& arr, map<INT,INT>& sorted) {
    INT elem = arr[0];
    arr.erase(arr.begin());
    sorted[elem] -= 1;
    if(sorted[elem] == 0) {
        sorted.erase(elem);
    }
}

INT findUniqueMin(map<INT,INT>& sorted) {
    INT min = 0;
    for(map<INT,INT>::const_iterator i=sorted.begin();i!=sorted.end();++i) {
        if((i->first - min) > 0) {
            return min;
        }
        min = i->first + 1;
    }
    return min;
}

INT findMin(INT n, INT k, INT a, INT b, INT c, INT r) {
    vector<INT> arr;
    map<INT, INT> sorted;
    addElement(arr, sorted, a);
    for(int i=1;i<k;++i) {
        INT val = ((b * arr[i-1]) + c) % r;
        addElement(arr, sorted, val);
    }
    for(int i=k;i<n;++i) {
        int min = findUniqueMin(sorted);
        addElement(arr, sorted, min);
        deleteElement(arr, sorted);
    }
    return arr[k-1];
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: FindMin <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        INT n, k, a, b, c, r;
        if(fscanf(fp, "%lld,%lld,%lld,%lld,%lld,%lld",
                  &n, &k, &a, &b, &c, &r) != 6) {
            continue;
        }
        printf("%lld\n", findMin(n, k, a, b, c, r));
    }
    fclose(fp);
    return 0;
}
