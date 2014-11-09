//
// Challenge name: Sum of Primes
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/4/
// Compile       : g++ -Wall -g -o SumOfPrimes SumOfPrimes.cpp
//

#include <stdio.h>

#define LIMIT 1000

int isPrime(int n) {
    //@todo: use sqrt(n) as the upper limit
    int limit = n >> 1;
    int i;
    if(n <= 1) {
        return 0;
    }
    for(i=2;i<limit;i++) {
        if(!(n % i)) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char** argv) {
    int i, sum, num;
    for(i=1,sum=2,num=1;i<LIMIT;num+=2) { // 2 is prime!
        if(isPrime(num)) {
            sum += num;
            i++;
        }
    }
    printf("%d\n", sum);
    return 0;
}
