//
// Challenge name: Sum of integers
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/17/
// Compile       : g++ -Wall -g -o SumOfIntegers SumOfIntegers.cpp
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192
// max number of integers in a line
#define MAX_INTS 1024


int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

int getInt(char* str, int start, int end) {
    int i, factor, sum, sign;
    sign = 1;
    for(i=end-1,factor=1,sum=0;i>start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    if(str[start] == '-') {
        sign = -1;
    }
    else {
        sum += (str[start] - '0') * factor;
    }
    sum *= sign;
    return sum;
}

int findNextComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

int findNextNonSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] != ' ') {
            return start;
        }
    }
    return start;
}

void printMaxSum(int* arr, int num) {
    int i, j, k, n, sum;
    int max = 0xffffffff;
    for(i=0;i<num;i++) {  // sequence length
        k = num - i;
        for(j=0;j<k;j++) { // phase shift along the array
            sum = 0;
            for(n=0;n<=i;n++) {
                sum += arr[j+n];
            }
            if(sum > max) {
                max = sum;
            }
        }
    }
    printf("%d\n", max);
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int arr[MAX_INTS];
    int i, j, num, len;

    if(argc != 2) {
        printf("USAGE: SumOfIntegers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        num = 0;
        for(i=0;i<len;) {
            j = findNextComma(currentLine, i, len);
            arr[num] = getInt(currentLine, i, j);
            num++;
            j = findNextNonSpace(currentLine, j+1, len);
            i = j;
        }
        if(num <= 0) {
            continue;
        }
        printMaxSum(arr, num);
    }
    fclose(fp);
    return 0;
}
