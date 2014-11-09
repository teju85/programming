//
// Challenge name: Palindromic Ranges
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/47/
// Compile       : gcc -Wall -g -o PalindromicRanges PalindromicRanges.c
//

#include <stdio.h>

#define MAX_DIGITS 10

int isPalindrome(int n) {
    int arr[MAX_DIGITS];
    int temp, i, j;
    for(i=0,temp=n;temp;i++,temp/=10) {
        arr[i] = temp % 10;
    }
    for(i--,j=0;i>j;i--,j++) {
        if(arr[i] != arr[j]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    FILE* fp;
    int L, R;
    int s, e, numI, prevI;

    if(argc != 2) {
        printf("USAGE: PalindromicRanges <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        L = -1;
        R = -2;
        fscanf(fp, "%d%d", &L, &R);
        if(L > R) {
            continue;
        }
        numI = 0;
        for(s=L;s<=R;s++) {
            prevI = isPalindrome(s)? 0 : 1;
            numI += prevI;
            for(e=s+1;e<=R;e++) {
                if(isPalindrome(e)) {
                    prevI = (prevI)? 0 : 1;
                }
                numI += prevI;
            }
        }
        printf("%d\n", numI);
    }
    fclose(fp);
    return 0;
}
