//
// Challenge name: Text Dollar
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/52/
// Compile       : g++ -Wall -g -o TextDollar TextDollar.cpp
//

#include <stdio.h>


void printDigit(int dig) {
    char* str[] = { "Zero", "One", "Two",   "Three", "Four",
                    "Five", "Six", "Seven", "Eight", "Nine", };
    if((dig >= 0) && (dig <= 9)) {
        printf("%s", str[dig]);
    }
}

void printTeens(int teens) {
    char* str[] = { "Ten",      "Eleven",   "Twelve",  "Thirteen",
                    "Fourteen", "Fifteen",  "Sixteen", "Seventeen",
                    "Eighteen", "Nineteen", };
    if((teens >= 10) && (teens <= 19)) {
        printf("%s", str[teens-10]);
    }
}

void printTens(int tens) {
    int t, d;
    char* str[] = { "",      "",      "Twenty",  "Thirty", "Forty",
                    "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", };
    if(tens >= 100) {
        return;
    }
    t = tens / 10;
    d = tens % 10;
    if(t == 0) {
        printDigit(d);
    }
    else if(t == 1) {
        printTeens(tens);
    }
    else {
        printf("%s", str[t]);
        if(d) {
            printDigit(d);
        }
    }
}

void printHundreds(int num) {
    int tens = num % 100;
    int dig = num / 100;
    if(num <= 999) {
        if(dig) {
            printDigit(dig);
            printf("Hundred");
        }
        printTens(tens);
    }
}

void printThousands(int num) {
    int thou = num / 1000;
    int hun = num % 1000;
    if(num <= 999999) {
        if(thou) {
            printHundreds(thou);
            printf("Thousand");
        }
        printHundreds(hun);
    }
}

void printMillions(int num) {
    int mil = num / 1000000;
    int thou = num % 1000000;
    if(num <= 999999999) {
        if(mil) {
            printHundreds(mil);
            printf("Million");
        }
        printThousands(thou);
        printf("Dollars\n");
    }
}

int main(int argc, char** argv) {
    int num;
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: TextDollar <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        num = -1;
        fscanf(fp, "%d", &num);
        if(num <= 0) {
            continue;
        }
        printMillions(num);
    }
    fclose(fp);
    return 0;
}
