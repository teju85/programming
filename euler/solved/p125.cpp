//
// Challenge name: Problem 125
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=125
// Compile       : g++ -Wall -g -o p125 p125.cpp
// Run           : ./p125
//

#include <stdio.h>
#include <map>
#include "include/integers.h"

#define INT long long int

INT sumOfAllNumbers(INT limit) {
    INT lmt = sqrt_int<INT>(limit);
    INT sum = 0;
    std::map<INT, bool> nums;
    for(INT i=1;i<=lmt;++i) {
        for(INT j=i+1;j<=lmt;++j) {
            INT num = sumOfSquaresBetween<INT>(i, j);
            if(num >= limit) {
                break;
            }
            if(is_palindrome<INT>(num) && (nums.find(num) == nums.end())) {
                sum += num;
                //printf("num=%lld consecutive=(%lld,%lld) sum=%lld\n",
                //       num, i, j, sum);
                nums[num] = true;
            }
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    printf("%lld\n", sumOfAllNumbers(100000000));
    return 0;
}
