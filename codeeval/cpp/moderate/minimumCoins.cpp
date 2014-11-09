//
// Challenge name: Minimum Coins.
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/74/
// Compile       : g++ -Wall -g -o minimumCoins minimumCoins.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: minimumCoins <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = 0;
        fscanf(fp, "%d", &num);
        if(num <= 0) {
            continue;
        }
        int min = 0;
        if(num >= 5) {
            min += (num / 5);
            num %= 5;
        }
        if(num >= 3) {
            min += (num / 3);
            num %= 3;
        }
        min += num;
        printf("%d\n", min);
    }
    fclose(fp);
    return 0;
}
