//
// Challenge name: Email Validation
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/35/
// Compile       : gcc -Wall -g -o EmailValidation EmailValidation.c
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192


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

int findChar(char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return -1;
}

int isAlphaNumeric(char c) {
    if((c >= 'a') && (c <= 'z')) return 1;
    if((c >= 'A') && (c <= 'Z')) return 1;
    if((c >= '0') && (c <= '9')) return 1;
    return 0;
}


int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int len, at, i;
    char c;

    if(argc != 2) {
        printf("USAGE: EmailValidation <fileContainingTestVectors>\n");
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
        // @ character must be present
        at = findChar(currentLine, 0, len, '@');
        if(at == -1) {
            printf("false\n");
            continue;
        }
        // valid user name
        for(i=0;i<at;i++) {
            c = currentLine[i];
            if(isAlphaNumeric(c)) continue;
            if((i == 0) || (i == at-1)) {
                break;  // non-alphanumeric chars at beginning and end!
            }
            if((c == '_') || (c == '.')) continue;
            break; // invalid char found
        }
        if(i < at) { // premature termination of for-loop
            printf("false\n");
            continue;
        }
        // valid domain name
        at++;
        for(i=at;i<len;i++) {
            c = currentLine[i];
            if(isAlphaNumeric(c)) continue;
            if((i == 0) || (i == at-1)) {
                break;  // non-alphanumeric chars at beginning and end!
            }
            // cannot appear at the beginning and end
            if((c == '.') || (c == '-')) continue;
            break; // invalid char found
        }
        if(i < len) { // premature termination of for-loop
            printf("false\n");
            continue;
        }
        printf("true\n");
    }
    fclose(fp);
    return 0;
}
