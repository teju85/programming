//
// Challenge name: Lowest Unique Number
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/103/
// Compile       : g++ -Wall -g -o LowestUniqueNumber LowestUniqueNumber.cpp
//

#include <stdio.h>
#define MAX_LINE 64

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

void sort(char* str, int* id, int len) {
    for(int i=0;i<len;++i) {
        for(int j=i+1;j<len;++j) {
            if(str[i] > str[j]) {
                char ctemp = str[i];
                str[i] = str[j];
                str[j] = ctemp;
                int itemp = id[i];
                id[i] = id[j];
                id[j] = itemp;
            }
        }
    }
}

#define MAX 20
int lowestUnique(char* str, int len) {
    char nums[MAX];
    int players[MAX];
    int playerId = 0;
    for(int i=0;i<len;++i) {
        if(str[i] == ' ') {
            continue;
        }
        nums[playerId] = str[i];
        players[playerId] = playerId + 1;
        ++playerId;
    }
    sort(nums, players, playerId);
    --playerId;
    char prevNum = '\0';
    for(int i=0;i<playerId;++i) {
        if(prevNum == nums[i]) {
            continue;
        }
        prevNum = nums[i];
        if(nums[i] == nums[i+1]) {
            continue;
        }
        return players[i];
    }
    return (prevNum != nums[playerId])? players[playerId] : 0;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: LowestUniqueNumber <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        printf("%d\n", lowestUnique(currentLine, len));
    }
    fclose(fp);
    return 0;
}
