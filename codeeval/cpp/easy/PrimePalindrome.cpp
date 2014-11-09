//
// Challenge name: Prime Palindrome
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/3/
// Compile       : g++ -Wall -g -o PrimePalindrome PrimePalindrome.cpp
//

#include <stdio.h>

#define LIMIT 1000
#define MAX_DIGITS 10

int isPrime(int n) {
    //@todo: use sqrt(n) as the upper limit
    int limit = n >> 1;
    int i;
    for(i=2;i<limit;i++) {
        if(!(n % i)) {
            return 0;
        }
    }
    return 1;
}

int isPalin(int n) {
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
    int i;
    for(i=LIMIT;i>=1;i--) {
        if(isPrime(i) && isPalin(i)) {
            break;
        }
    }
    printf("%d\n", i);
    return 0;
}
