//
// Challenge name: Problem 52
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=52
// Compile       : g++ -Wall -g -o p52 p52.cpp
// Run           : ./p52
//

#include <stdio.h>
#define INT int
#define HIST_LEN 10

INT hist1[HIST_LEN];
INT hist2[HIST_LEN];

void get_digits_hist(INT* hist, INT a) {
    for(INT i=0;i<HIST_LEN;++i) {
        hist[i] = 0;
    }
    while(a) {
        INT t = a % 10;
        ++hist[t];
        a /= 10;
    }
}

bool compare_hist(INT* hista, INT* histb) {
    for(int i=0;i<HIST_LEN;++i) {
        if(hista[i] != histb[i]) {
            return false;
        }
    }
    return true;
}

bool isCompatible(INT num) {
    if(num <= 0) {
        return false;
    }
    get_digits_hist(hist1, num);
    get_digits_hist(hist2, num<<1);
    if(!compare_hist(hist1, hist2)) {
        return false;
    }
    get_digits_hist(hist2, num*3);
    if(!compare_hist(hist1, hist2)) {
        return false;
    }
    get_digits_hist(hist2, num<<2);
    if(!compare_hist(hist1, hist2)) {
        return false;
    }
    get_digits_hist(hist2, num*6);
    return compare_hist(hist1, hist2);
}

int main(int argc, char** argv) {
    for(INT i=1;;i*=10) {
        INT lim = (i * 10) / 6;
        for(INT j=i-1;j<=lim;++j) {
            if(isCompatible(j)) {
                printf("%d\n", j);
                return 0;
            }
        }
    }
    return 0;
}
