//
// Challenge name: N Mod M
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/62/
// Compile       : g++ -Wall -g -o NmodM NmodM.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: NmodM <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    int n, m;
    while(!feof(fp)) {
        n = m = 0;
        fscanf(fp, "%d,%d", &n, &m);
        if(m == 0) {
            continue;
        }
        int quotient = n / m;
        int remainder = n - (quotient * m);
        printf("%d\n", remainder);
    }
    fclose(fp);
    return 0;
}
