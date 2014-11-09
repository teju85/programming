//
// Challenge name: Next Number
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/44/
// Compile       : gcc -Wall -g -o NextNumber NextNumber.c
//

#include <stdio.h>

#define MAX_DIGITS 10

int digits[MAX_DIGITS];
int numDigits;
int numZeros;
void genDigits(int num) {
    int i, temp;
    for(i=0;i<MAX_DIGITS;i++) {
        digits[i] = 0;
    }
    numZeros = 0;
    for(i=0,temp=num;temp;i++,temp/=10) {
        digits[i] = temp % 10;
        if(!digits[i]) {
            numZeros++;
        }
    }
    numDigits = i;
}

void getFirstMin(int from, int* min, int* pos) {
    int i, m, p;
    int barrier = 0;
    int increasing;
    m = digits[from];
    p = from;
    for(i=from+1;i<numDigits;i++) {
        if(digits[i] > digits[i-1]) {
            increasing = 1;
        }
        else {
            increasing = 0;
            if(digits[i] > digits[from]) {
                m = digits[from];
                p = from;
                break;
            }
        }
        if(digits[i] < m) {
            m = digits[i];
            p = i;
            break;
        }
        // barrier for jumping found!
        // consider even 'equality' for the above condition check!
        if(digits[i] > digits[from]) {
            barrier = 1;
            continue;
        }
        // barrier with equality means stop here!
        if(barrier  &&  (digits[i] == m)) {
            m = digits[from];
            p = from;
            break;
        }
    }
    *min = m;
    *pos = p;
}

void swapArray(int s1, int s2) {
    int temp = digits[s1];
    digits[s1] = digits[s2];
    digits[s2] = temp;
}

void arrayShift(int s1, int s2) {
    int i;
    for(i=s1;i<s2;i++) {
        swapArray(i, i+1);
    }
}

void sortTill(int e) {
    int i, j;
    if(e >= numDigits) {
        return;
    }
    for(i=0;i<=e;i++) {
        for(j=i+1;j<=e;j++) {
            if(digits[i] < digits[j]) {
                swapArray(i, j);
            }
        }
    }
}

int getNum() {
    int i, num, temp;
    for(i=0,num=0,temp=1;i<numDigits;i++,temp*=10) {
        num += (digits[i] * temp);
    }
    return num;
}

int sortAndGetNum() {
    int i, j;
    // sort in descending order
    for(i=0;i<numDigits;i++) {
        for(j=i+1;j<numDigits;j++) {
            if(digits[i] < digits[j]) {
                swapArray(i, j);
            }
        }
    }
    // you are entering higher-digit area now!
    numDigits++;
    numZeros++;
    digits[numDigits-1] = 0;
    // get the least non-zero digit and swap it with last number
    swapArray(numDigits-1, numDigits-numZeros-1);
    return getNum();
}

int main(int argc, char** argv) {
    FILE* fp;
    int num, i, swapMade;
    int min, minPos;

    if(argc != 2) {
        printf("USAGE: NextNumber <fileContainingTestVectors>\n");
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
        if(num < 0) {
            continue;
        }
        genDigits(num);
        swapMade = 0;
        for(i=0;i<numDigits;i++) {
            getFirstMin(i, &min, &minPos);
            // no minimum found, move to the next index
            if(minPos == i) {
                continue;
            }
            arrayShift(i, minPos);
            sortTill(minPos-1);
            swapMade = 1;
            break;
        }
        if(swapMade) {
            printf("%d\n", getNum());
        }
        else {
            printf("%d\n", sortAndGetNum());
        }
    }
    fclose(fp);
    return 0;
}
