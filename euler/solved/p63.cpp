//
// Challenge name: Problem 63
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=63
// Compile       : g++ -Wall -g -o p63 p63.cpp -lm
// Run           : ./p63
//

#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    int num = 1;  // 1^1 is also true
    for(int i=1;i<10;++i) {
        double li = log10(i);
        for(int n=1;;++n) {
            int d = (int)ceil(li * n);
            if(d != n) {
                break;
            }
            ++num;
            printf("%d %d %.0lf\n", i, n, pow(i, n));
        }
    }
    printf("total = %d\n", num);
    return 0;
}
