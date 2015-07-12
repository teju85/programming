//
// Challenge name: Column Names
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/197/
// Compile       : g++ -Wall -g -o ColumnNames ColumnNames.cpp
//

#include <stdio.h>

char name(int num) {
    return ('A' + (char)num);
}

void column2name(int num) {
    const int count = 3;
    int vals[count];
    for(int i=0;i<count;++i) {
        vals[i] = -1;
    }
    for(int i=0;i<count;++i) {
        vals[i] = num % 26;
        num /= 26;
        if(num <= 0) {
            break;
        }
        --num;
    }
    for(int i=count-1;i>=0;--i) {
        if(vals[i] >= 0) {
            printf("%c", name(vals[i]));
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ColumnNames <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = -1;
        if(fscanf(fp, "%d", &num) != 1) {
            continue;
        }
        column2name(num-1);
    }
    fclose(fp);
    return 0;
}
