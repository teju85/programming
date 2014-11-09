//
// Challenge name: Problem 206
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=206
// Compile       : g++ -Wall -g -o p206 p206.cpp -lm
// Run           : ./p206
//

#include <stdio.h>
#include <math.h>

#define INT unsigned long long int

bool doesSatisfyCondition(INT num) {
    if(num % 100) {
        return false;
    }
    num /= 100;
    for(INT i=9;i>=1;--i) {
        if((num % 10) != i) {
            return false;
        }
        num /= 100;
    }
    return true;
}

int main(int argc, char** argv) {
    // these define the max-min range for the squares
    INT high = 1929394959697989900ULL;
    INT low  = 1020304050607080900ULL;
    high = 2000000000000000000ULL;
    low  = 1000000000000000000ULL;

    // 2nd last digit of the square has to be '0'
    // Because, there can't be any squares ending with only one '0'.
    // Hence, the square root's last digit is '0'.
    //
    // Since the 3rd last digit is '9', the square root's 2nd last
    // digit is '3'.
    INT sqrt_high = (INT) sqrt((double)high);
    sqrt_high = (100 * (sqrt_high / 100)) + 100;
    INT sqrt_low  = (INT) sqrt((double)low);
    sqrt_low = (100 * (sqrt_low / 100)) - 100;
    printf("sqrt-range = (%llu,%llu)\n", sqrt_high, sqrt_low);
    printf("sqrt-range-size = %llu\n", (sqrt_high - sqrt_low));
    printf("sq-range = (%llu,%llu)\n",
           (sqrt_high*sqrt_high), (sqrt_low*sqrt_low));

    // actual loop
    for(INT num=sqrt_low;num<=sqrt_high;num+=10) {
        INT sq = num * num;
        if(doesSatisfyCondition(sq)) {
            printf("num=%llu square=%llu\n", num, sq);
            break;
        }
    }
    return 0;
}
