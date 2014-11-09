//
// Challenge name: Problem 79
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=79
// Compile       : g++ -Wall -g -o p79 p79.cpp
// Run           : ./p79 p79.txt
//

#include <stdio.h>
#include "include/integers.h"

int graph[10][10];
int hist[10];
int before[10];
int nums[10];

void printGraph() {
    printf("Graph:\n");
    for(int i=0;i<10;++i) {
        for(int j=0;j<10;++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("Occurence:\n");
    for(int i=0;i<10;++i) {
        printf("%d ", hist[i]);
    }
    printf("\n");
    printf("Before:\n");
    for(int i=0;i<10;++i) {
        printf("%d ", before[i]);
    }
    printf("\n");
    printf("Sorted predecessors:\n");
    for(int i=0;i<10;++i) {
        if(hist[nums[i]]) {
            printf("%d ", nums[i]);
        }
    }
    printf("\n");
    printf("Precedence among those numbers having %s\n",
           "same number of predecessors will resolve their order");
}

void initialize(FILE* fp) {
    for(int i=0;i<10;++i) {
        before[i] = 0;
        hist[i] = 0;
        nums[i] = i;
        for(int j=0;j<10;++j) {
            graph[i][j] = 0;
        }
    }
    int num;
    fscanf(fp, "%d", &num);
    for(int i=0;i<num;++i) {
        int entry;
        fscanf(fp, "%d", &entry);
        int a, b, c;
        c = entry % 10;
        entry /= 10;
        b = entry % 10;
        entry /= 10;
        a = entry % 10;
        graph[a][b] = 1;
        graph[b][c] = 1;
        hist[a] = hist[b] = hist[c] = 1;
        //printGraph();
    }
    // number of predecessors
    for(int i=0;i<10;++i) {
        for(int j=0;j<10;++j) {
            before[j] += graph[i][j];
        }
    }
    // sort ascendingly based on number of predecessors
    int temp[10];
    for(int i=0;i<10;++i) {
        temp[i] = before[i];
    }
    for(int i=0;i<10;++i) {
        for(int j=i;j<10;++j) {
            if(temp[i] > temp[j]) {
                swap<int>(temp[i], temp[j]);
                swap<int>(nums[i], nums[j]);
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p79 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    initialize(fp);
    fclose(fp);
    printGraph();
    return 0;
}
