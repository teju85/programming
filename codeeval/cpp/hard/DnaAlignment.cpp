//
// Challenge name: DNA Alignment
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/171/
// Compile       : g++ -Wall -g -o DnaAlignment DnaAlignment.cpp
//

#include <stdio.h>
#define MAX_LINE 2048

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

int findBar(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == '|') {
            return start;
        }
    }
    return start;
}

const int gapOpening = -8;
const int gapExtension = -1;
const int match = 3;
const int misMatch = -3;

int editDistance(const char* s, int slen, const char* t, int tlen) {
    int** mid = new int*[slen+1];
    int** low = new int*[slen+1];
    int** up = new int*[slen+1];
    for(int i=0;i<=slen;++i) {
        mid[i] = new int[tlen+1];
        low[i] = new int[tlen+1];
        up[i] = new int[tlen+1];
        for(int j=0;j<=tlen;++j) {
            mid[i][j] = low[i][j] = up[i][j] = 0;
        }
    }
    low[1][0] = up[0][1] = mid[0][1] = mid[1][0] = gapOpening;
    for(int i=2;i<=slen;++i) {
        low[i][0] = low[i-1][0] + gapExtension;
        mid[i][0] = mid[i-1][0] + gapExtension;
    }
    for(int j=2;j<=tlen;++j) {
        up[0][j] = up[0][j-1] + gapExtension;
        mid[0][j] = mid[0][j-1] + gapExtension;
    }
    for(int i=1;i<=slen;++i) {
        for(int j=1;j<=tlen;++j) {
            int lower = (i==1)? gapOpening :  low[i-1][j] + gapExtension;
            int tmp = mid[i-1][j] + gapOpening;
            if(tmp > lower) {
                lower = tmp;
            }
            int upper = (j==1)? gapOpening :  up[i][j-1] + gapExtension;
            tmp = mid[i][j-1] + gapOpening;
            if(tmp > upper) {
                upper = tmp;
            }
            low[i][j] = lower;
            up[i][j] = upper;
            int midder = lower;
            if(upper > midder) {
                midder = upper;
            }
            tmp = mid[i-1][j-1];
            tmp += (s[i-1] == t[j-1])? match : misMatch;
            if(tmp > midder) {
                midder = tmp;
            }
            mid[i][j] = midder;
        }
    }
    int dist = mid[slen][tlen];
    for(int i=0;i<=slen;++i) {
        delete [] mid[i];
        delete [] up[i];
        delete [] low[i];
    }
    delete [] mid;
    delete [] up;
    delete [] low;
    return dist;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DnaAlignment <fileContainingTestVectors>\n");
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
        int pos = findBar(currentLine, 0, len);
        printf("%d\n", editDistance(currentLine, pos-1, currentLine+pos+2, len-pos-2));
    }
    fclose(fp);
    return 0;
}
