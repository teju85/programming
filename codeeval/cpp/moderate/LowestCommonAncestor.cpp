//
// Challenge name: Lowest Common Ancestor
// Difficulty    : moderate
// Link          : http://codeeval.com/open_challenges/11/
// Compile       : gcc -Wall -g -o LowestCommonAncestor LowestCommonAncestor.c
//

#include <stdio.h>

#define NUMNODES 7
#define MAXANS 4

int nodes[NUMNODES] = { 30,  8, 52,  3, 20, 10, 29 };
// assumption: the tree given in the link above has been used
// to generate this 'ancestor-list'
// one can get this by doing a DFS on the tree
int ancestors[NUMNODES][MAXANS] = {
    {  0,  0,  0,  0 },
    { 30,  0,  0,  0 },
    { 30,  0,  0,  0 },
    {  8, 30,  0,  0 },
    {  8, 30,  0,  0 },
    { 20,  8, 30,  0 },
    { 20,  8, 30,  0 }
};

int findNode(int node) {
    int i;
    for(i=0;i<NUMNODES;i++) {
        if(nodes[i] == node) {
            return i;
        }
    }
    return -1;
}

int numAncestors(int node) {
    int i, j;
    i = findNode(node);
    if(i < 0) {
        return -1;
    }
    for(j=0;j<MAXANS;j++) {
        if(!ancestors[i][j]) {
            return j;
        }
    }
    return -1;
}

int main(int argc, char** argv) {
    FILE* fp;
    int n1, n2, na1, na2, i, j, ni1, ni2;

    if(argc != 2) {
        printf("USAGE: LowestCommonAncestor <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        n1 = n2 = -1;
        fscanf(fp, "%d%d", &n1, &n2);
        if((n1 < 0) || (n2 < 0)) {
            continue;
        }
        ni1 = findNode(n1);
        ni2 = findNode(n2);
        na1 = numAncestors(n1);
        na2 = numAncestors(n2);
        if((na1 < 0) || (na2 < 0)) {
            printf("\n");
            continue;
        }
        for(i=0;i<=na1;i++) {
            for(j=0;j<=na2;j++) {
                if(ancestors[ni1][i] == ancestors[ni2][j]) {
                    printf("%d", ancestors[ni1][i]);
                    break;
                }
            }
            if(j <= na2) {
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
