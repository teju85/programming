//
// Challenge name: File Size
// Difficulty    : easy
// Link          : http://codeeval.com/open_challenges/26/
// Compile       : g++ -Wall -g -o FileSize FileSize.cpp
//

#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fp;
    int fSize;

    if(argc != 2) {
        printf("USAGE: FileSize <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    fseek(fp, 0, SEEK_END);
    fSize = (int) ftell(fp);
    printf("%d\n", fSize);
    fclose(fp);
    return 0;
}
