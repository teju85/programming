//
// Challenge name: Sum of Integers from File
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/24/
// Compile       : g++ -Wall -g -o SumOfIntegers SumOfIntegers.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int sum, num;

    if(argc != 2) {
        printf("USAGE: SumOfIntegers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    sum = 0;
    while(!feof(fp)) {
        num = -1;
        fscanf(fp, "%d", &num);
        if(num == -1) {
            continue;
        }
        sum += num;
    }
    printf("%d\n", sum);
    fclose(fp);
    return 0;
}
