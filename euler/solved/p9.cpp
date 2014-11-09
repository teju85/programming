//
// Challenge name: Problem 9
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=9
// Compile       : g++ -Wall -g -o p9 p9.cpp
// Run           : ./p9
//
#include <stdio.h>


int main(int argc, char** argv) {
    int a, b, k, k2;
    k = 1000;
    k2 = k >> 1;
    // a + b + c = k
    // a^2 + b^2 = c^2
    // a < b < c
    // So, a + b = (k/2) + (a*b/k)
    // So, a * b is divisible by k
    for(a=1;a<k;++a) {
        for(b=a+1;b<k;++b) {
            int n = a * b;
            if(n % k) {
                continue;
            }
            n /= k;
            if(k2 + n  ==  a + b) {
                int abc = a * b * (k - a - b);
                printf("%d\n", abc);
                return 0;
            }
        }
    }
    return 0;
}
