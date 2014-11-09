//
// Challenge name: Problem 2
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=2
// Compile       : g++ -Wall -g -o p2 p2.cpp
// Run           : ./p2
//

#include <stdio.h>

#define MAX_FIBO 4000000

int main(int argc, char** argv) {
    int sum = 0;
    int f1 = 0;
    int f2 = 1;
    while(f2 < MAX_FIBO) {
        if(!(f2 & 0x1)) {
            sum += f2;
        }
        int next = f1 + f2;
        f1 = f2;
        f2 = next;
    }
    printf("%d\n", sum);
    return 0;
}
