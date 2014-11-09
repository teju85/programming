//
// Challenge name: Stack Implementation
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/9/
// Compile       : gcc -Wall -g -o StackImplementation StackImplementation.c
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192
// max number of integers in a line
#define MAX_INTS 1024


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

int getInt(char* str, int start, int end) {
    int i, factor, sum, sign;
    sign = 1;
    for(i=end-1,factor=1,sum=0;i>start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
    if(str[start] == '-') {
        sign = -1;
    }
    else {
        sign = 1;
        sum += (str[start] - '0') * factor;
    }
    sum *= sign;
    return sum;
}

int findNextSpace(char* str, int start, int len) {
    for(;start<len;start++) {
        if(str[start] == ' ') {
            return start;
        }
    }
    return start;
}

typedef struct {
    int arr[MAX_INTS];
    int top;
} stack;

void initStack(stack* s) {
    s->top = -1;
}

void push(stack* s, int val) {
    s->top++;
    s->arr[s->top] = val;
}

int isEmpty(stack* s) {
    return (s->top < 0);
}

int pop(stack* s) {
    if(isEmpty(s)) {
        return 0xffffffff;
    }
    int v = s->arr[s->top];
    s->top--;
    return v;
}

int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE];
    stack s;
    int i, j, len, num;

    if(argc != 2) {
        printf("USAGE: StackImplementation <fileContainingTestVectors>\n");
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
        initStack(&s);
        num = 0;
        for(i=0;i<len;) {
            j = findNextSpace(currentLine, i, len);
            push(&s, getInt(currentLine, i, j));
            i = j + 1;
            num++;
        }
        if(num <= 0) {
            continue;
        }
        printf("%d", pop(&s));
        while(!isEmpty(&s)) {
            pop(&s);
            if(!isEmpty(&s)) {
                printf(" %d", pop(&s));
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
