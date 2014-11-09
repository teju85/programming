//
// Challenge name: Problem 59
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=59
// Compile       : g++ -Wall -g -o p59 p59.cpp
// Run           : ./p59 p59.txt
//
#include <stdio.h>
#include "include/characters.h"

#define NUM_CHARS 4096
char en_data[NUM_CHARS];
char de_data[NUM_CHARS];
int en_data_len;


bool all_valid_text() {
    for(int i=0;i<en_data_len;++i) {
        if(!valid_text(de_data[i])) {
            return false;
        }
    }
    return true;
}

bool contains_substring(char* sub, int len) {
    int limit = en_data_len - len;
    for(int i=0;i<limit;++i) {
        if(de_data[i] == sub[0]) {
            int j = 1;
            for(;j<len;++j) {
                if(de_data[i+j] != sub[j]) {
                    break;
                }
            }
            if(j >= len) {
                return true;
            }
        }
    }
    return false;
}

bool contains_some_common_words() {
    int num = 0;
    num += contains_substring((char*)" the ", 4);
    num += contains_substring((char*)" for ", 4);
    num += contains_substring((char*)" is ", 4);
    num += contains_substring((char*)" an ", 4);
    num += contains_substring((char*)" a ", 3);
    if(num >= 3) {
        return true;
    }
    return false;
}

// assumptions:
//  1. en_data_len is perfectly divisible by 3
//  2. encryption key length = 3
//  3. encryption key contains only lowercase english alphabets
void decrypt() {
    bool found = false;
    char c1, c2, c3;
    for(c1='a';c1<='z';++c1) {
        for(c2='a';c2<='z';++c2) {
            for(c3='a';c3<='z';++c3) {
                for(int i=0;i<en_data_len;i+=3) {
                    de_data[i] = en_data[i] ^ c1;
                    de_data[i+1] = en_data[i+1] ^ c2;
                    de_data[i+2] = en_data[i+2] ^ c3;
                }
                if(all_valid_text() && contains_some_common_words()) {
                    found = true;
                    break;
                }
            }
            if(found) {
                break;
            }
        }
        if(found) {
            break;
        }
    }
    if(!found) {
        printf("Key not found!\n");
        return;
    }
    int sum = 0;
    for(int i=0;i<en_data_len;++i) {
        sum += (int)de_data[i];
        printf("%c", de_data[i]);
    }
    printf("\n");
    printf("Key=%c%c%c\n", c1, c2, c3);
    printf("Sum = %d\n", sum);
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p59 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    en_data_len = 0;
    while(!feof(fp)) {
        int temp = -1;
        fscanf(fp, "%d,", &temp);
        if(temp < 0) {
            break;
        }
        en_data[en_data_len] = (char)temp;
        ++en_data_len;
    }
    fclose(fp);
    decrypt();
    return 0;
}
