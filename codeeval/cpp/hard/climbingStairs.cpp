//
// Challenge name: Climbing Stairs
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/64/
// Compile       : g++ -Wall -g -o climbingStairs climbingStairs.cpp
//

#include <stdio.h>

void countNumWays(int steps, int current, int& numWays) {
    if(current > steps) {
        return;
    }
    if(current == steps) {
        numWays++;
        return;
    }
    countNumWays(steps, current+1, numWays);
    countNumWays(steps, current+2, numWays);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: climbingStairs <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int steps = 0;
        fscanf(fp, "%d", &steps);
        if(steps <= 0) {
            continue;
        }
        int numWays = 0;
        countNumWays(steps, 0, numWays);
        printf("%d\n", numWays);
    }
    fclose(fp);
    return 0;
}
