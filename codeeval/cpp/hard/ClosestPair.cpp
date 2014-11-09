//
// Challenge name: Closest Pair
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/51/
// Compile       : g++ -Wall -lm -g -o ClosestPair ClosestPair.cpp
//

#include <stdio.h>
#include <math.h>

#define NUM_POINTS 10000
#define MAX_DIST   10000


int eucledean_square(int x1, int y1, int x2, int y2) {
    int xd = x1 - x2;
    int yd = y1 - y2;
    return ((xd * xd) + (yd * yd));
}

int main(int argc, char** argv) {
    int pts[NUM_POINTS][2];
    int i, j, k, num_pts, min_dist_sq;
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ClosestPair <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        fscanf(fp, "%d", &num_pts);
        if(num_pts <= 0) {
            break;
        }
        for(i=0;i<num_pts;++i) {
            fscanf(fp, "%d%d", &(pts[i][0]), &(pts[i][1]));
        }
        min_dist_sq = MAX_DIST;
        for(i=0;i<num_pts;++i) {
            for(j=i+1;j<num_pts;++j) {
                k = eucledean_square(pts[i][0], pts[i][1],
                                     pts[j][0], pts[j][1]);
                if(k < min_dist_sq) {
                    min_dist_sq = k;
                }
            }
        }
        if(min_dist_sq >= MAX_DIST) {
            printf("INFINITY\n");
        }
        else {
            printf("%.4f\n", sqrt(min_dist_sq));
        }
    }
    fclose(fp);
    return 0;
}
