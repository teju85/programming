//
// Challenge name: Discount Offers
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/48/
// Compile       : g++ -Wall -g -o DiscountOffers DiscountOffers.cpp
//

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
#define MAX_LINE 4096
using namespace std;

void getCustomerProducts(char* str, int len, vector<string>* cust, vector<string>* prod) {
    vector<string>* curr = cust;
    string temp;
    for(int i=0;i<len;++i) {
        if((str[i] == '\0') || (str[i] == '\n') || (str[i] == '\r')) {
            curr->push_back(temp);
            return;
        }
        if(str[i] == ',') {
            curr->push_back(temp);
            temp = "";
            continue;
        }
        if(str[i] == ';') {
            curr->push_back(temp);
            temp = "";
            curr = prod;
            continue;
        }
        temp += str[i];
    }
}

int numLetters(const char* str, int len) {
    int num = 0;
    for(--len;len>=0;--len) {
        char c = (char)tolower(str[len]);
        if(isalpha(c)) {
            ++num;
        }
    }
    return num;
}

bool isVowel(char c) {
    if((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
        return true;
    }
    return false;
}

int numVowels(const char* str, int len) {
    int num = 0;
    for(--len;len>=0;--len) {
        char c = (char)tolower(str[len]);
        if(isVowel(c)) {
            ++num;
        }
    }
    return num;
}

int numConsonants(const char* str, int len) {
    int num = 0;
    for(--len;len>=0;--len) {
        char c = (char)tolower(str[len]);
        if(isalpha(c) && !isVowel(c)) {
            ++num;
        }
    }
    return num;
}

int gcd(int a, int b) {
    while(b > 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

float getSS(const string& a, const string& b) {
    const char* s1 = a.c_str();
    int len1 = (int)a.size();
    int numL1 = numLetters(s1, len1);
    const char* s2 = b.c_str();
    int len2 = (int)b.size();
    int numL2 = numLetters(s2, len2);
    int g = gcd(numL1, numL2);
    float SS = (numL2 & 0x1)? numConsonants(s1, len1) : numVowels(s1, len1) * 1.5;
    if(g != 1) {
        SS *= 1.5;
    }
    return SS;
}

float maxTotalSS(float** ss, int numc, int nump) {
    return 0;
}

float maximizeTotalSS(const vector<string>& cust, const vector<string>& prod) {
    int numc = (int)cust.size();
    int nump = (int)prod.size();
    float** ss = new float*[numc];
    for(int i=0;i<numc;++i) {
        ss[i] = new float[nump];
        for(int j=0;j<nump;++j) {
            ss[i][j] = getSS(cust[i], prod[j]);
        }
    }
    float max = maxTotalSS(ss, numc, nump);
    for(int i=0;i<numc;++i) {
        delete [] ss[i];
    }
    delete [] ss;
    return max;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DiscountOffers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        if(currentLine[0] == '\0') {
            continue;
        }
        vector<string> customers;
        vector<string> products;
        getCustomerProducts(currentLine, MAX_LINE, &customers, &products);
        printf("%.2f\n", maximizeTotalSS(customers, products));
    }
    fclose(fp);
    return 0;
}
