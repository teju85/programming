//
// Challenge name: NUMBER OPERATIONS
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/190/
// Compile       : g++ -Wall -g -o NumberOperations NumberOperations.cpp
//

#include <stdio.h>

enum Operations {
    PLUS = 0,
    MINUS,
    TIMES,
    MAX
};

int eval(int v1, int v2, Operations op) {
    switch(op) {
    case PLUS:  return v1 + v2;
    case MINUS: return v1 - v2;
    case TIMES: return v1 * v2;
    default:    return 0;
    }
}

int eval(int val1, int val2, int val3, int val4, int val5,
         Operations op1, Operations op2, Operations op3, Operations op4) {
    int res = eval(val1, val2, op1);
    res = eval(res, val3, op2);
    res = eval(res, val4, op3);
    res = eval(res, val5, op4);
    return res;
}

bool canGet42(int val1, int val2, int val3, int val4, int val5) {
    for(int i=PLUS;i<MAX;++i) {
        for(int j=PLUS;j<MAX;++j) {
            for(int k=PLUS;k<MAX;++k) {
                for(int m=PLUS;m<MAX;++m) {
                    int res = eval(val1, val2, val3, val4, val5,
                                   (Operations)i, (Operations)j, (Operations)k,
                                   (Operations)m);
                    if(res == 42) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool permCanGet42(int* val) {
    for(int i=0;i<5;++i) {
        for(int j=0;j<5;++j) {
            if(j == i) continue;
            for(int k=0;k<5;++k) {
                if((k == j) || (k == i)) continue;
                for(int m=0;m<5;++m) {
                    if((m == k) || (m == j) || (m == i)) continue;
                    for(int n=0;n<5;++n) {
                        if((n == m) || (n == k) || (n == j) || (n == i)) continue;
                        if(canGet42(val[i], val[j], val[k], val[m], val[n])) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: NumberOperations <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    int val[5];
    while(!feof(fp)) {
        if(fscanf(fp, "%d%d%d%d%d", val+0, val+1, val+2, val+3, val+4) != 5) {
            continue;
        }
        printf("%s\n", permCanGet42(val)? "YES" : "NO");
    }
    fclose(fp);
    return 0;
}
