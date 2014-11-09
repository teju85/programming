//
// Challenge name: String List
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/38/
// Compile       : gcc -Wall -g -o StringList StringList.c
//

#include <stdio.h>
// assuming that line contains only 2048 characters
#define MAX_LINE 2048

int numPrinted;

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

int findComma(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ',') {
            return start;
        }
    }
    return start;
}

int getInt(char* str, int start, int end) {
    int i, factor, sum;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    return sum;
}

int getUniques(char* str, int start, int end, char* uniq) {
    int U;
    char uniques[52];  // only alphabets (case-sensitive)! [a-zA-Z]
    int i, v;
    // unique characters
    for(i=0;i<52;i++) {
        uniques[i] = 0;
    }
    for(i=start;i<end;i++) {
        if((str[i] >= 'a') && (str[i] <= 'z')) {
            v = (int) (str[i]-'a');
            uniques[v] = 1;
        }
        else if((str[i] >= 'A') && (str[i] <= 'Z')) {
            v = (int) (str[i] - 'A' + 26);
            uniques[v] = 1;
        }
    }
    // number of unique characters
    U = 0;
    for(i=0;i<52;i++) {
        U += uniques[i];
    }
    for(i=0,v=0;i<52;i++) {
        if(uniques[i]) {
            uniq[v] = (i < 26)? (char)(i + 'a') : (char)(i + 'A' + 26);
            v++;
        }
    }
    uniq[v] = '\0';
    return U;
}

void printStr(char* str) {
    if(numPrinted) {
        printf(",");
    }
    printf("%s", str);
    numPrinted++;
}

void enumerate(char* str, int base, int N) {
    int i, numStrs, j, k;
    char line[MAX_LINE];
    // number of enumerations for this base
    for(i=1,numStrs=1;i<=N;i++,numStrs*=base);
    // each enumeration
    line[N] = '\0';
    for(i=0;i<numStrs;i++) {
        k = i;
        for(j=N-1,k=i;j>=0;j--,k/=base) {
            line[j] = str[k % base];
        }
        printStr(line);
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE], chars[MAX_LINE];
    int len, rem, N, U;

    if(argc != 2) {
        printf("USAGE: StringList <fileContainingTestVectors>\n");
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
        // number and the string
        rem = findComma(currentLine, 0, len);
        N = getInt(currentLine, 0, rem);
        rem++;
        // unique chars
        U = getUniques(currentLine, rem, len, chars);
        if(U <= 0) {
            continue;
        }
        // enumeration
        numPrinted = 0;
        enumerate(chars, U, N);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
