//
// Challenge name: Digit Statistics
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/144/
// Compile       : g++ -Wall -g -o DigitStatistics DigitStatistics.cpp
//

#include <stdio.h>
#include <vector>
using namespace std;
#define DIGITS 10
#define INT long long int

struct histogram {
    histogram(): mat() { init(); }
    ~histogram() {}
    void evaluate(INT a, INT n) {
        for(INT i=0;i<DIGITS;++i) {
            arr[i] = 0LL;
        }
        INT len = (INT)mat[a].size();
        for(INT i=0;i<len;++i) {
            INT digit = mat[a][i];
            INT numTimes = (n - i + len - 1) / len;
            arr[digit] = numTimes;
        }
    }
    void print() const {
        printf("%lld: %lld", 0LL, arr[0]);
        for(INT i=1;i<DIGITS;++i) {
            printf(", %lld: %lld", i, arr[i]);
        }
        printf("\n");
    }
private:
    void init() {
        mat.push_back(vector<INT>());  // 0
        mat.push_back(vector<INT>());  // 1
        vector<INT> two;
        two.push_back(2);
        two.push_back(4);
        two.push_back(8);
        two.push_back(6);
        mat.push_back(two);
        vector<INT> three;
        three.push_back(3);
        three.push_back(9);
        three.push_back(7);
        three.push_back(1);
        mat.push_back(three);
        vector<INT> four;
        four.push_back(4);
        four.push_back(6);
        mat.push_back(four);
        vector<INT> five;
        five.push_back(5);
        mat.push_back(five);
        vector<INT> six;
        six.push_back(6);
        mat.push_back(six);
        vector<INT> seven;
        seven.push_back(7);
        seven.push_back(9);
        seven.push_back(3);
        seven.push_back(1);
        mat.push_back(seven);
        vector<INT> eight;
        eight.push_back(8);
        eight.push_back(4);
        eight.push_back(2);
        eight.push_back(6);
        mat.push_back(eight);
        vector<INT> nine;
        nine.push_back(9);
        nine.push_back(1);
        mat.push_back(nine);
    }
    vector<vector<INT> > mat;
    INT arr[DIGITS];
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: DigitStatistics <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    histogram hist;
    INT a, n;
    while(!feof(fp)) {
        if(fscanf(fp, "%lld%lld", &a, &n) == 2) {
            hist.evaluate(a, n);
            hist.print();
        }
    }
    fclose(fp);
    return 0;
}
