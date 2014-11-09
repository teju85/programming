//
// Challenge name: Problem 24
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=24
// Compile       : g++ -Wall -g -o p24 p24.cpp
// Run           : ./p24
//

#include <stdio.h>
#define PERMUTE_NUM 1000000
int num_permutes = 0;


// circular rotate right among the elements from s to p (both inclusive)
void ror(char* str, int s, int p) {
    int i;
    char t = str[p];
    for(i=p;i>s;--i) {
        str[i] = str[i-1];
    }
    str[i] = t;
}

// circular rotate left among the elements from s to p (both inclusive)
void rol(char* str, int s, int p) {
    int i;
    char t = str[s];
    for(i=s;i<p;++i) {
        str[i] = str[i+1];
    }
    str[i] = t;
}

void permute(char* str, int loc, int len) {
    if(num_permutes >= PERMUTE_NUM) {
        printf("%s\n", str);
        return;
    }
    int i;
    if(loc >= len-1) {
        ++num_permutes;
        if(num_permutes >= PERMUTE_NUM) {
            printf("%s\n", str);
            return;
        }
        return;
    }
    for(i=loc;i<len;++i) {
        ror(str, loc, i);
        permute(str, loc+1, len);
        if(num_permutes >= PERMUTE_NUM) {
            return;
        }
        rol(str, loc, i);
    }
}

int main(int argc, char** argv) {
    char str[] = "0123456789";
    permute(str, 0, 10);
    return 0;
}
