//
// Challenge name: Problem 30
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=30
// Compile       : g++ -Wall -g -o p30 p30.cpp
// Run           : ./p30
//

#include <stdio.h>
#define LIMIT 1000000
#define INT int

INT fifthPowerDigitSum(INT d) {
    INT sum = 0;
    while(d) {
        INT g = d % 10;
        d /= 10;
        sum += (g * g * g * g * g);
    }
    return sum;
}

int main(int argc, char** argv) {
    INT sum = 0;
    for(INT num=2;num<=LIMIT;++num) {
        if(fifthPowerDigitSum(num) == num) {
            printf("%d\n", num);
            sum += num;
        }
    }
    printf("sum=%d\n", sum);
    return 0;
}
