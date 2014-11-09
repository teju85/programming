//
// Challenge name: Message Decoding
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/36/
// Compile       : gcc -Wall -g -o MessageDecoding MessageDecoding.c
//

#include <stdio.h>
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

int binaryString2int(char* str, int len) {
    int val = 0;
    int i, j;
    for(i=0,j=len-1;i<len;i++,j--) {
        val += ((str[i] - '0') << j);
    }
    return val;
}

int getIdx(int val, int kLen) {
    int i, sum;
    for(i=1,sum=0;i<kLen;i++) {
        sum += ((1 << i) - 1);
    }
    return (sum + val);
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    int hLen, len, i, kLen, val, max;
    char c;

    if(argc != 2) {
        printf("USAGE: MessageDecoding <fileContainingTestVectors>\n");
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
        // number of headers
        for(hLen=0;hLen<len;hLen++) {
            c = currentLine[hLen];
            if((c == '0') || (c == '1')) {
                break;
            }
        }
        // decoding part
        for(i=hLen;i<len;) {
            kLen = binaryString2int(currentLine+i, 3);
            i += 3;
            if(kLen <= 0) {  // end of encoded stream
                break;
            }
            max = (1 << kLen) - 1;
            val = 0;
            while(val != max) {
                val = binaryString2int(currentLine+i, kLen);
                i += kLen;
                if(val >= max) { // end of current segment
                    break;
                }
                printf("%c", currentLine[getIdx(val, kLen)]);
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
