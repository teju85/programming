//
// Challenge name: Not So Clever
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/232/
// Compile       : g++ -Wall -g -o NotSoClever NotSoClever.cpp
//

#include <stdio.h>
#include <vector>

int readVec(std::vector<int>& vec, FILE* fp) {
    int count = 0;
    int val;
    while(!feof(fp) && (fscanf(fp, "%d", &val) == 1)) {
        vec.push_back(val);
    }
    fscanf(fp, "|");
    fscanf(fp, "%d", &count);
    return count;
}

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void stupidSort(std::vector<int>& vec, int count) {
    int len = (int)vec.size();
    for(int i=0;i<count;++i) {
        for(int j=1;j<len;++j) {
            if(vec[j-1] > vec[j]) {
                swap(vec[j-1], vec[j]);
                break;
            }
        }
    }
}

void print(const std::vector<int>& vec) {
    bool first = true;
    for(std::vector<int>::const_iterator itr=vec.begin();itr!=vec.end();++itr) {
        if(first) {
            printf("%d", *itr);
            first = false;
        } else {
            printf(" %d", *itr);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: NotSoClever <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        std::vector<int> vec;
        int count = readVec(vec, fp);
        if(count <= 0) {
            continue;
        }
        stupidSort(vec, count);
        print(vec);
    }
    fclose(fp);
    return 0;
}
