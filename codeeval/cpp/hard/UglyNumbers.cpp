//
// Challenge name: Ugly Numbers
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/42/
// Compile       : gcc -Wall -g -o UglyNumbers UglyNumbers.c
//

#include <stdio.h>
#define MAX_CHARS 14
#define MAX_LEN 28

typedef long int   int64;


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

int isUgly(int64 num) {
    if(!num)       return 1;  // special case
    if(!(num & 1)) return 1;  // divisible by 2
    if(!(num % 3)) return 1;  // divisible by 3
    if(!(num % 5)) return 1;  // divisible by 5
    if(!(num % 7)) return 1;  // divisible by 7
    return 0;
}

int64 getInt64(char* str, int start, int end) {
    int64 factor, sum;
    int i;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    return sum;
}

void int2tertiary(int* arr, int max, int idx) {
    int i;
    for(i=0;i<max;i++,idx/=3) {
        arr[i] = idx % 3;
    }
}

int generateEqn(char* eqn, int* ops, char* str, int numC) {
    int i, j, numLoc;
    numLoc = numC - 1;
    eqn[0] = str[0];
    for(i=0,j=1;i<numLoc;i++) {
        if(ops[i] == 1) {
            eqn[j] = '+';
            j++;
        }
        else if(ops[i] == 2) {
            eqn[j] = '-';
            j++;
        }
        eqn[j] = str[i+1];
        j++;
    }
    eqn[j] = '\0';
    return j;
}

int64 evaluateEqn(char* eqn, int eLen) {
    int64 val;
    int s, i;
    char op = '0';
    for(val=0,i=0,s=0;i<eLen;i++) {
        if(eqn[i] == '-') {
            if(op == '0') {
                val = getInt64(eqn, s, i);
            }
            else if(op == '-') {
                val -= getInt64(eqn, s, i);
            }
            else if(op == '+') {
                val += getInt64(eqn, s, i);
            }
            s = i + 1;
            op = '-';
        }
        else if(eqn[i] == '+') {
            if(op == '0') {
                val = getInt64(eqn, s, i);
            }
            else if(op == '-') {
                val -= getInt64(eqn, s, i);
            }
            else if(op == '+') {
                val += getInt64(eqn, s, i);
            }
            s = i + 1;
            op = '+';
        }
    }
    // remnant
    if(op == '0') {
        val = getInt64(eqn, s, i);
    }
    else if(op == '-') {
        val -= getInt64(eqn, s, i);
    }
    else if(op == '+') {
        val += getInt64(eqn, s, i);
    }
    return val;
}

int main(int argc, char** argv) {
    FILE* fp;
    char str[MAX_CHARS];
    char eqn[MAX_LEN];
    int ops[MAX_CHARS];  // none, '-' or '+'
    int numC, numPossible, numLoc;
    int i, eLen, numU;
    int64 val;

    if(argc != 2) {
        printf("USAGE: UglyNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        str[0] = '\0';
        fgets(str, MAX_CHARS, fp);
        numC = stringLen(str, MAX_CHARS);
        if(str[0] == '\0') {
            continue;
        }
        if(numC <= 0) {
            continue;
        }
        // special case
        if(numC == 1) {
            printf("%d\n", (isUgly(getInt64(str, 0, 1)))? 1 : 0);
            continue;
        }
        numLoc = numC - 1;
        numU = 0;
        // number of possibilities
        numPossible = 1;
        for(i=1;i<numC;++i,numPossible*=3);
        // enumerate all of them!
        for(i=0;i<numPossible;++i) {
            int2tertiary(ops, numLoc, i);
            eLen = generateEqn(eqn, ops, str, numC);
            val = evaluateEqn(eqn, eLen);
            if(isUgly(val)) {
                ++numU;
            }
            //printf("%s  %ld %d %d\n", eqn, val, numU, i);
        }
        printf("%d\n", numU);
    }
    fclose(fp);
    return 0;
}
