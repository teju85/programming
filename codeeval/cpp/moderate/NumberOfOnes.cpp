//
// Challenge name: Number of Ones
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/16/
// Compile       : g++ -Wall -g -o NumberOfOnes NumberOfOnes.cpp
//

#include <stdio.h>

int numOnes[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                    1, 2, 2, 3, 2, 3, 3, 4 };

int main(int argc, char** argv) {
    FILE* fp;
    int i, sum, num;

    if(argc != 2) {
        printf("USAGE: NumberOfOnes <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        num = -1;
        fscanf(fp, "%d", &num);
        if(num == -1) {
            continue;
        }
        sum = 0;
        for(i=0;i<32;i+=4) {
            sum += numOnes[(num >> i) & 0xf];
        }
        printf("%d\n", sum);
    }
    fclose(fp);
    return 0;
}
