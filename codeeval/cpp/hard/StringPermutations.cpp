//
// Challenge name: String Permutations
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/14/
// Compile       : gcc -Wall -g -o StringPermutations StringPermutations.c
//

#include <stdio.h>
// assuming that line contains only 2048 characters
#define MAX_LINE 2048

int numPrinted;

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

//@todo: use something else other than this bubble sort for performance!
void sortStr(char* str, int len) {
    int i, j;
    char t;
    for(i=0;i<len;i++) {
        for(j=i+1;j<len;j++) {
            if(str[i] > str[j]) {
                t = str[i];
                str[i] = str[j];
                str[j] = t;
            }
        }
    }
}

void printPerm(char* str) {
    if(!numPrinted) {
        printf("%s", str);
    }
    else {
        printf(",%s", str);
    }
    numPrinted++;
}

// circular rotate right among the elements from s to p (both inclusive)
void ror(char* str, int s, int p) {
    int i;
    char t = str[p];
    for(i=p;i>s;i--) {
        str[i] = str[i-1];
    }
    str[i] = t;
}

// circular rotate left among the elements from s to p (both inclusive)
void rol(char* str, int s, int p) {
    int i;
    char t = str[s];
    for(i=s;i<p;i++) {
        str[i] = str[i+1];
    }
    str[i] = t;
}

// wrt the starting the position, figure out whether the
// previous character is same or not
int sameAsPrevious(char* str, int loc, int start) {
    if(loc == start) {
        return 0;
    }
    if(str[loc-1] == str[loc]) {
        return 1;
    }
    return 0;
}

void permuteNprint(char* str, int loc, int len) {
    int i;
    if(loc >= len-1) {
        printPerm(str);
        return;
    }
    for(i=loc;i<len;i++) {
        // if there are repetitions in the string, then they'll
        // result in same sequence. So, do not recurse on them!
        // This will work because, the input string is assumed
        // to be sorted in ascending order.
        if(sameAsPrevious(str, i, loc)) {
            continue;
        }
        ror(str, loc, i);
        permuteNprint(str, loc+1, len);
        rol(str, loc, i);
    }
}


int main(int argc, char** argv) {
    char currentLine[MAX_LINE];
    FILE* fp;
    int len;

    if(argc != 2) {
        printf("USAGE: StringPermutations <fileContainingTestVectors>\n");
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
        numPrinted = 0;
        sortStr(currentLine, len);
        // now, since the elements in the string are sorted in
        // ascending order, the below call will print out all
        // the UNIQUE permutations in ascending order.
        permuteNprint(currentLine, 0, len);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
