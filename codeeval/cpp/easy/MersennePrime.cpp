//
// Challenge name: Mersenne Prime
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/240/
// Compile       : g++ -Wall -g -o MersennePrime MersennePrime.cpp
//

#include <stdio.h>
#include <vector>

bool isPrime(int n) {
    //@todo: use sqrt(n) as the upper limit
    int limit = n >> 1;
    int i;
    for(i=2;i<limit;i++) {
        if(!(n % i)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: MersennePrime <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int limit;
        if(fscanf(fp, "%d", &limit) != 1) {
            continue;
        }
        int num = 3;
        std::vector<int> primes;
        while(num < limit) {
            if(isPrime(num)) {
                primes.push_back(num);
            }
            num = ((num + 1) << 1) - 1;
        }
        std::vector<int>::const_iterator itr = primes.begin();
        printf("%d", *itr);
        ++itr;
        for(;itr!=primes.end();++itr) {
            printf(", %d", *itr);
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
