//
// Challenge name: Roman Numerals
// Difficulty    : easy
// Link          : https://www.codeeval.com/open_challenges/106/
// Compile       : g++ -Wall -g -o RomanNumerals RomanNumerals.cpp
//

#include <stdio.h>
#include <string>
using namespace std;

void thousands(int d, string& str) {
    switch(d) {
    case 3: str += 'M';
    case 2: str += 'M';
    case 1: str += 'M';
    };
}

void hundreds(int d, string& str) {
    switch(d) {
    case 9:
        str += "CM";
        break;
    case 8:
        str += "DCCC";
        break;
    case 7:
        str += "DCC";
        break;
    case 6:
        str += "DC";
        break;
    case 5:
        str += 'D';
        break;
    case 4:
        str += "CD";
        break;
    case 3: str += 'C';
    case 2: str += 'C';
    case 1: str += 'C';
    };
}

void tens(int d, string& str) {
    switch(d) {
    case 9:
        str += "XC";
        break;
    case 8:
        str += "LXXX";
        break;
    case 7:
        str += "LXX";
        break;
    case 6:
        str += "LX";
        break;
    case 5:
        str += 'L';
        break;
    case 4:
        str += "XL";
        break;
    case 3: str += 'X';
    case 2: str += 'X';
    case 1: str += 'X';
    };
}

void ones(int d, string& str) {
    switch(d) {
    case 9:
        str += "IX";
        break;
    case 8:
        str += "VIII";
        break;
    case 7:
        str += "VII";
        break;
    case 6:
        str += "VI";
        break;
    case 5:
        str += 'V';
        break;
    case 4:
        str += "IV";
        break;
    case 3: str += 'I';
    case 2: str += 'I';
    case 1: str += 'I';
    };
}

void printRoman(int num) {
    string str;
    thousands(num / 1000, str);
    num %= 1000;
    hundreds(num / 100, str);
    num %= 100;
    tens(num / 10, str);
    num %= 10;
    ones(num, str);
    printf("%s\n", str.c_str());
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RomanNumerals <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int num = -1;
        fscanf(fp, "%d", &num);
        if(num <= 0) {
            continue;
        }
        printRoman(num);
    }
    fclose(fp);
    return 0;
}
