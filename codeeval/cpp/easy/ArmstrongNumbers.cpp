//
// Challenge name: Armstrong Numbers
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/82/
// Compile       : g++ -Wall -g -o ArmstrongNumbers ArmstrongNumbers.cpp
//

#include <stdio.h>

#define INT unsigned long long

int numDigits(INT num) {
    int digitCount = 0;
    while(num) {
        num /= 10;
        ++digitCount;
    }
    return digitCount;
}

INT intPow(INT base, INT exp) {
    INT pow = 1;
    for(INT i=0;i<exp;++i) {
        pow *= base;
    }
    return pow;
}

bool isArmstrongNumber(INT num) {
    int digitCount = numDigits(num);
    INT val = num;
    INT sum = 0;
    while(val) {
        INT digit = val % 10;
        val /= 10;
        sum += intPow(digit, digitCount);
    }
    return (num == sum);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ArmstrongNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        INT num = 0;
        fscanf(fp, "%llu", &num);
        if(num == 0) {
            continue;
        }
        printf("%s\n", isArmstrongNumber(num)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
