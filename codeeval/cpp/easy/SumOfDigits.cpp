//
// Challenge name: Sum of Digits
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/21/
// Compile       : gcc -Wall -g -o SumOfDigits SumOfDigits.c
//

#include <stdio.h>

int digitSum(int n) {
    int sum;
    for(sum=0;n;n/=10) {
        sum += n % 10;
    }
    return sum;
}

int main(int argc, char** argv) {
    FILE* fp;
    int num;

    if(argc != 2) {
        printf("USAGE: MultiplesOfANumber <fileContainingTestVectors>\n");
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
        printf("%d\n", digitSum(num));
    }
    fclose(fp);
    return 0;
}
