//
// Challenge name: N Mod M
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/62/
// Compile       : g++ -Wall -g -o MmodM[D[D[D[N MmodM[D[D[D[N.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
FILE* fp;

if(argc != 2) {
    printf("USAGE: MmodM[D[D[D[N <fileContainingTestVectors>\n");
    return 1;
}
fp = fopen(argv[1], "r");
if(fp == NULL) {
    printf("Failed to open the input file '%s' for reading!\n", argv[1]);
    return 2;
}
while(!feof(fp)) {
}
fclose(fp);
    return 0;
}
