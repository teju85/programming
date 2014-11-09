//
// Challenge name: Problem 99
// Difficulty    : medium
// Link          : http://projecteuler.net/index.php?section=problems&id=99
// Compile       : g++ -Wall -g -o p99 p99.cpp -lm
// Run           : ./p99 p99.txt
//

#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p99 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    int num_pairs;
    fscanf(fp, "%d", &num_pairs);
    float max = -1.0f;
    int line = -1;
    for(int i=1;i<=num_pairs;++i) {
        int base, exp;
        fscanf(fp, "%d,%d", &base, &exp);
        float log = logf(base) * (float)exp;
        if(log > max) {
            max = log;
            line = i;
        }
    }
    fclose(fp);
    printf("%d\n", line);
    return 0;
}
