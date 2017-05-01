//
// Challenge name: ALTERNATIVE REALITY
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/223/
// Compile       : g++ -Wall -g -o AlternativeReality AlternativeReality.cpp
//

#include <stdio.h>

const int coins[] = {1, 5, 10, 25, 50};
const int nCoins = sizeof(coins) / sizeof(coins[0]);
const int maxNum = 150;

int count(int num, int** table) {
    for(int i=0;i<nCoins;++i) {
        table[0][i] = 1;
    }
    for(int i=1;i<=num+1;++i) {
        for(int j=0;j<nCoins;++j) {
            int with = (i-coins[j] >= 0)? table[i-coins[j]][j] : 0;
            int without = table[i][j-1];
            table[i][j] = with + without;
        }
    }
    return table[num][nCoins-1];
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: AlternativeReality <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    int** table = new int*[maxNum+1];
    for(int i=0;i<=maxNum;++i) {
        table[i] = new int[nCoins];
    }
    while(!feof(fp)) {
        int num;
        if(fscanf(fp, "%d", &num) != 1) {
            continue;
        }
        printf("%d\n", count(num, table));
    }
    for(int i=0;i<maxNum;++i) {
        delete [] table[i];
    }
    delete [] table;
    fclose(fp);
    return 0;
}
