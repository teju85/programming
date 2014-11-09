//
// Challenge name: Repeated Substring
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/53/
// Compile       : g++ -Wall -g -o RepeatedSubstring RepeatedSubstring.cpp
//

#include <stdio.h>
#define MAX_LINE 8192

typedef struct {
    char* s;
    int len;
} Substr;

int ss_equal(Substr a, Substr b) {
    int i;
    if(a.len != b.len) {
        return 0;
    }
    for(i=0;i<a.len;++i) {
        if(a.s[i] != b.s[i]) {
            return 0;
        }
    }
    return 1;
}

int ss_all_spaces(Substr a) {
    int i;
    if(a.len <= 0) {
        return 1;
    }
    for(i=0;i<a.len;++i) {
        if(a.s[i] !=  ' ') {
            return 0;
        }
    }
    return 1;
}

void ss_print(Substr a) {
    int i;
    if(a.len <= 0) {
        printf("NONE\n");
        return;
    }
    for(i=0;i<a.len;++i) {
        printf("%c", a.s[i]);
    }
    printf("\n");
}

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

void printLongestRepeated(char* str, int len) {
    Substr longest = {NULL, 0};
    Substr temp, temp1;
    int i, j, k, m, num, r;
    int reps = 0;
    for(i=0;i<len;++i) {
        for(j=i;j<len;++j) {
            m = j - i + 1; // length of current substring
            if(m < longest.len) {
                continue;
            }
            temp.s = str + i;
            temp.len = m;
            if(ss_all_spaces(temp)) {
                continue;
            }
            num = 0;
            r = len - m + 1;
            for(k=j+1;k<r;++k) {
                temp1.s = str + k;
                temp1.len = m;
                if(ss_equal(temp, temp1)) {
                    ++num;
                    k += (m - 1); // repeated sub-strings may not overlap
                }
            }
            // no repitition
            if(num <= 0) {
                continue;
            }
            if(m > longest.len) {
                longest = temp;
                reps = num;
            }
            else {  // sub-strings of same length
                if(reps < num) {
                    longest = temp;
                    reps = num;
                }
            }
        }
    }
    ss_print(longest);
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int len;

    if(argc != 2) {
        printf("USAGE: RemoveCharacters <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        printLongestRepeated(currentLine, len);
    }
    fclose(fp);
    return 0;
}
