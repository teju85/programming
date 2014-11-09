//
// Challenge name: Odd Numbers
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/25/
// Compile       : g++ -Wall -g -o OddNumbers OddNumbers.cpp
//

#include <stdio.h>

#define START_NUM 1
#define END_NUM   99

int main(int argc, char** argv) {
    int begin = (START_NUM & 0x1)? START_NUM : START_NUM + 1;
    int i;
    for(i=begin;i<=END_NUM;i+=2) {
        printf("%d\n", i);
    }
    return 0;
}
