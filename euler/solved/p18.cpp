//
// Challenge name: Problem 18
// Difficulty    : easy
// Link          : http://projecteuler.net/index.php?section=problems&id=18
// Compile       : g++ -Wall -g -o p18 p18.cpp
// Run           : ./p18 p18.txt
//
#include <stdio.h>
#include "include/integers.h"
#define MAX_ELEMENTS 60000

int main(int argc, char** argv) {
    int arr[MAX_ELEMENTS];
    int rows;
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: p18 <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open '%s' for reading!\n", argv[1]);
        return 2;
    }
    fscanf(fp, "%d", &rows);
    for(int i=0;i<MAX_ELEMENTS;++i) {
        arr[i] = 0;
    }
    int num_ele = triangle_sum<int>(rows);
    for(int i=0;i<num_ele;++i) {
        fscanf(fp, "%d", &(arr[i]));
    }
    fclose(fp);
    arr[1] += arr[0];
    arr[2] += arr[0];
    for(int r=3;r<=rows;++r) {
        int previous = triangle_sum<int>(r-2);
        int present = triangle_sum<int>(r-1);
        arr[present] += arr[previous];
        for(int i=r-2;i>=1;--i) {
            int a = previous + i - 1;
            int b = a + 1;
            arr[present+i] += (arr[a] > arr[b])? arr[a] : arr[b];
        }
        arr[present+r-1] += arr[previous+r-2];
    }
    int sum = 0;
    int present = triangle_sum<int>(rows-1);
    for(;present<num_ele;++present) {
        if(sum < arr[present]) {
            sum = arr[present];
        }
    }
    printf("%d\n", sum);
    return 0;
}
