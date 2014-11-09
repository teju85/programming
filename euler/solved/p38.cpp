//
// Challenge name: Problem 38
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=38
// Compile       : g++ -Wall -g -o p38 p38.cpp
// Run           : ./p38
//

#include <stdio.h>

#define INT long long int



void _updateHist(int a, int* hist) {
    while(a) {
        int r = a % 10;
        a /= 10;
        hist[r]++;
    }
}

bool is1to9Pandigital(int* arr, int len) {
    int hist[10];
    for(int i=0;i<10;++i) {
        hist[i] = 0;
    }
    for(int i=0;i<len;++i) {
        _updateHist(arr[i], hist);
    }
    if(hist[0] != 0) {
        return false;
    }
    for(int i=1;i<10;++i) {
        if(hist[i] != 1) {
            return false;
        }
    }
    return true;
}

int numDigits(int a) {
    int num = 0;
    while(a) {
        ++num;
        a /= 10;
    }
    return num;
}

INT concatenate(int* arr, int len) {
    INT num = 0;
    for(--len;len>=0;--len) {
        int d = numDigits(num);
        INT pow = 1;
        for(;d>0;--d) {
            pow *= 10;
        }
        num += (pow * arr[len]);
    }
    return num;
}

INT workOnProduct(int i) {
    int j, digits;
    int arr[10];
    for(j=1,digits=0;;++j) {
        int num = i * j;
        arr[j-1] = num;
        digits += numDigits(num);
        if(digits > 9) {
            break;
        }
        if(digits == 9) {
            if(is1to9Pandigital(arr, j)) {
                return concatenate(arr, j);
            }
            break;
        }
    }
    return -1;
}

INT largestPandigital() {
    INT largest = 0;
    // single/double/triple/quadruple digits
    for(int i=1;i<=9999;++i) {
        INT num = workOnProduct(i);
        if(num > largest) {
            largest = num;
        }
    }
    return largest;
}

int main(int argc, char** argv) {
    printf("%lld\n", largestPandigital());
    return 0;
}
