//
// Challenge name: Simple Calculator
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/94/
// Compile       : g++ -Wall -lm -g -o SimpleCalculator SimpleCalculator.cpp
//

#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>
#include <ctype.h>
using namespace std;

enum Operator {
    UNARY_MINUS,
    EXPONENT,
    MULTIPLY,
    DIVIDE,
    ADD,
    SUBTRACT
};

enum Type {
    OP,
    NUM
};

struct Data {
    Type t;
    union {
        float value;
        Operator opr;
    } u;
};

typedef vector<Data> DataStack;

float str2num(const string& s) {
    stringstream ss(s);
    float pos;
    ss >> pos;
    return pos;
}

bool isEqual(Operator a, Operator b) {
    if(a == b) {
        return true;
    }
    if(((a == MULTIPLY) && (b == DIVIDE)) ||
       ((a == DIVIDE) && (b == MULTIPLY))) {
        return true;
    }
    if(((a == ADD) && (b == SUBTRACT)) ||
       ((a == SUBTRACT) && (b == ADD))) {
        return true;
    }
    return false;
}

bool isHigher(Operator a, Operator b) {
    return (a < b);
}

void print(float val) {
    char buff[32];
    int size = sprintf(buff, "%.5f", val);
    for(--size;size>=0;--size) {
        if(buff[size] != '0') {
            if(buff[size] == '.') {
                --size;
            }
            break;
        }
    }
    buff[size+1] = '\0';
    printf("%s\n", buff);
}

float evalExpression(FILE* fp) {
    DataStack nums;
    DataStack ops;
    float output = 0.0f;
    string val;
    char prevC = '\0';
    Type prevT = OP;
    while(!feof(fp)) {
        char c = fgetc(fp);
        if(c == '(') {
            Data dd;
            dd.t = NUM;
            dd.u.value = evalExpression(fp);
            nums.push_back(dd);
            prevT = NUM;
        }
        else if(isdigit(c) || (c == '.')) {
            val += c;
        }
        else if(c == ' ') {
            if(prevC == ' ') {
                continue;
            }
            if(val != "") {
                Data dd;
                dd.t = NUM;
                dd.u.value = str2num(val);
                nums.push_back(dd);
                val = "";
                prevT = NUM;
            }
        }
        else if(c == '-') {
            Data dd;
            dd.t = OP;
            dd.u.opr = (prevT == OP)? UNARY_MINUS : SUBTRACT;
            ops.push_back(dd);
            prevT = OP;
        }
        else if(c == '^') {
            Data dd;
            dd.t = OP;
            dd.u.opr = EXPONENT;
            ops.push_back(dd);
            prevT = OP;
        }
        else if(c == '*') {
            Data dd;
            dd.t = OP;
            dd.u.opr = MULTIPLY;
            ops.push_back(dd);
            prevT = OP;
        }
        else if(c == '/') {
            Data dd;
            dd.t = OP;
            dd.u.opr = DIVIDE;
            ops.push_back(dd);
            prevT = OP;
        }
        else if(c == '+') {
            Data dd;
            dd.t = OP;
            dd.u.opr = ADD;
            ops.push_back(dd);
            prevT = OP;
        }
        prevC = c;
    }
    return output;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: SimpleCalculator <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        printf("%f\n", evalExpression(fp));
    }
    fclose(fp);
    return 0;
}
