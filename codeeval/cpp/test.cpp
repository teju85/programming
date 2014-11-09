#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
using namespace std;
#define MOD (2*3*5*7)
string s;
long long dyn[41][MOD];

int main(int argc, char** argv) {
    FILE* fp;
    char str[40];
    if(argc != 2) {
        printf("USAGE: UglyNumbers <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        fscanf(fp, "%s", str);
        s = str;
        memset(dyn, 0, sizeof(dyn));
        dyn[0][0] = 1;
        for (int i = 0; i < s.size(); i++)
            for (int sgn = (i==0) ? 1 : -1; sgn <= 1; sgn += 2) {
                int cur = 0;
                for (int j = i; j < s.size(); j++) {
                    cur = (cur*10 + s[j]-'0')%MOD;
                    for (int x = 0; x < MOD; x++)
                        dyn[j+1][(x+sgn*cur+MOD)%MOD] += dyn[i][x];
                }
            }
        long long ret = 0;
        for (int x = 0; x < MOD; x++)
            if (x%2 == 0 || x%3 == 0 || x%5 == 0 || x%7 == 0)
                ret += dyn[s.size()][x];
        cout << ret << endl;
    }
    return 0;
}
