//
// Challenge name: Prefix expressions
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/7/
// Compile       : gcc -Wall -g -o PrefixExpressions PrefixExpressions.c
//

#include <stdio.h>
// assuming that line contains only 8192 characters
#define MAX_LINE 8192
#define MAX_OPS 128
#define MAX_INTS 256



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

int size(stack* s) {
    return (s->top + 1);
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

int isOperator(char* str, int pos) {
    if((str[pos] == '+') || (str[pos] == '*') || (str[pos] == '/')) {
        return 1;
    }
    return 0;
}

int getInt(char* str, int start, int end) {
    int i, factor, sum;
    for(i=end-1,factor=1,sum=0;i>=start;i--,factor*=10) {
        sum += (str[i] - '0') * factor;
    }
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

int operate(char op, int a, int b) {
    //printf("%d  %c  %d\n", a, op, b);
    switch(op) {
    case '*':
        return a * b;
    case '+':
        return a + b;
    case '/':
        return a / b;
    }
    return -1;
}


int main(int argc, char** argv) {
    FILE* fp;
    char currentLine[MAX_LINE], op;
    int len, i, j, numTop, a, b;
    stack vals, ops;

    if(argc != 2) {
        printf("USAGE: PrefixExpressions <fileContainingTestVectors>\n");
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
        initStack(&vals);
        initStack(&ops);
        numTop = 0;
        for(i=0;i<len;) {
            if(isOperator(currentLine, i)) {
                push(&ops, (int)currentLine[i]);
                i += 2;  // current operator followed by a space
                numTop = 0;  // restart the counter
                continue;
            }
            j = findNextSpace(currentLine, i, len);
            push(&vals, getInt(currentLine, i, j));
            numTop++;
            i = j + 1;
            if(numTop == 2) {
                // clear-off the 'adjacent' operands in the queue
                while(size(&vals) > 1) {
                    op = (char) pop(&ops);
                    b = pop(&vals);
                    a = pop(&vals);
                    a = operate(op, a, b);
                    push(&vals, a);
                }
                numTop = 1; // you'll be left with one element
            }
        }
        // work on the remaining operators
        while(!isEmpty(&ops)) {
            op = (char) pop(&ops);
            b = pop(&vals);
            a = pop(&vals);
            a = operate(op, a, b);
            push(&vals, a);
        }
        printf("%d\n", pop(&vals));
    }
    fclose(fp);
    return 0;
}
