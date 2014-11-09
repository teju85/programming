//
// Challenge name: Multiplication Tables
// Difficulty    : easy
// Link          : http://www.codeeval.com/open_challenges/23/
// Compile       : gcc -Wall -g -o MultiplicationTables MultiplicationTables.c
//

#include <stdio.h>

#define TABLES 12

int main(int argc, char** argv) {
    int i, j;
    for(i=1;i<=TABLES;i++) {
        printf("%d", i);
        if(i >= 10) {
            printf("%3d", i<<1);
        }
        else {
            printf("%4d", i<<1);
        }
        for(j=3;j<=TABLES;j++) {
            printf("%4d", i*j);
        }
        printf("\n");
    }
    return 0;
}
