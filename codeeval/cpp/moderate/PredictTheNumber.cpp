//
// Challenge name: Predict The Number
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/125/
// Compile       : g++ -Wall -g -o PredictTheNumber PredictTheNumber.cpp
//

#include <stdio.h>
#define MAX (unsigned int)~0

int ceilLog2(unsigned int num) {
    int log = 0;
    while(num) {
        num >>= 1;
        ++log;
    }
    return log;
}

int digitAt(unsigned int pos) {
    switch(pos) {
    case 0:  return 0;
    case 1:  return 1;
    case 2:  return 1;
    case 3:  return 2;
    default:
        int numDigits = ceilLog2(pos);
        unsigned int halfMax = (unsigned int) (1 << (numDigits - 1));
        int val = digitAt(pos-halfMax);
        switch(val) {
        case 0:  return 1;
        case 1:  return 2;
        case 2:  return 0;
        default: return -1;
        }
    }
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: PredictTheNumber <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        unsigned int pos = MAX;
        fscanf(fp, "%u", &pos);
        if(pos == MAX) {
            continue;
        }
        printf("%d\n", digitAt(pos));
    }
    fclose(fp);
    return 0;
}
