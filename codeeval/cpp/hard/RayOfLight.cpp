//
// Challenge name: Ray Of Light
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/176/
// Compile       : g++ -Wall -g -o RayOfLight RayOfLight.cpp
//

#include <stdio.h>
#include <vector>
#define MAX_LINE 128
#define ARENA_SIZE 10
using namespace std;

struct Ray {
    int x;
    int y;
    int angle;

    void proceed(int dim) {
        x = ((angle == 45) || (angle == 135))? x-1 : x+1;
        y = ((angle == 135) || (angle == 225))? y-1 : y+1;
    }

    void reflect(int dim) {
        // top
        if(x == 0) {
            angle = (angle == 45)? 315 : 225;
            ++x;
            return;
        }
        // bottom
        if(x == dim-1) {
            angle = (angle == 225)? 135 : 45;
            --x;
            return;
        }
        // left
        if(y == 0) {
            angle = (angle == 135)? 45 : 315;
            ++y;
            return;
        }
        // right
        if(y == dim-1) {
            angle = (angle == 315)? 225 : 135;
            --y;
            return;
        }
    }

    bool isAtCorner() const {
        return (((x == 0) && (y == 0)) ||
                ((x == ARENA_SIZE-1) && (y == 0)) ||
                ((x == 0) && (y == ARENA_SIZE-1)) ||
                ((x == ARENA_SIZE-1) && (y == ARENA_SIZE-1)));
    }
};

struct Arena {
    void populateArena(const char* c) {
        for(int i=0,k=0;i<ARENA_SIZE;++i) {
            for(int j=0;j<ARENA_SIZE;++j,++k) {
                area[i][j] = c[k];
            }
        }
        findFirstRay();
    }

    void runSimulation() {
        while(!rays.empty()) {
            nextMove();
            //print();
        }
    }

    void serialize() {
        for(int i=0;i<ARENA_SIZE;++i) {
            for(int j=0;j<ARENA_SIZE;++j) {
                printf("%c", area[i][j]);
            }
        }
        printf("\n");
    }

    void print() const {
        for(int i=0;i<ARENA_SIZE;++i) {
            for(int j=0;j<ARENA_SIZE;++j) {
                printf("%c", area[i][j]);
            }
            printf("\n");
        }
    }

private:
    char area[ARENA_SIZE][ARENA_SIZE];
    vector<Ray*> rays;
    Ray first;

    void nextMove() {
        Ray& r = *(rays[0]);
        r.proceed(ARENA_SIZE);
        if(r.isAtCorner()) {
            removeFirstRay();
            return;
        }
        // reached the hole?
        if((r.x == first.x) && (r.y == first.y)) {
            applyRay(r);
            removeFirstRay();
            return;
        }
        r.reflect(ARENA_SIZE);
        // column?
        if(area[r.x][r.y] == 'o') {
            removeFirstRay();
            return;
        }
        // prism?
        else if(area[r.x][r.y] == '*') {
            createPrismReflections(r);
        }
        // started to take an old step?
        if(((area[r.x][r.y] == '/') || (area[r.x][r.y] == 'X')) &&
           ((r.angle == 45) || (r.angle == 225))) {
            removeFirstRay();
            return;
        }
        else if(((area[r.x][r.y] == '\\') || (area[r.x][r.y] == 'X')) &&
           ((r.angle == 135) || (r.angle == 315))) {
            removeFirstRay();
            return;
        }
        applyRay(r);
    }

    void removeFirstRay() {
        delete rays[0];
        rays.erase(rays.begin());
    }

    void createPrismReflections(Ray& r) {
#define PUSH(a)                                    \
        do {                                       \
            Ray* r1 = new Ray;                     \
            r1->x = r.x;                           \
            r1->y = r.y;                           \
            r1->angle = a;                         \
            rays.push_back(r1);                    \
        } while(0)
        switch(r.angle) {
        case 45:
            PUSH(135);
            PUSH(315);
            --r.x;
            ++r.y;
            break;
        case 135:
            PUSH(45);
            PUSH(225);
            --r.x;
            --r.y;
            break;
        case 225:
            PUSH(135);
            PUSH(315);
            ++r.x;
            --r.y;
            break;
        default:
            PUSH(45);
            PUSH(225);
            ++r.x;
            ++r.y;
        };
#undef PUSH
    }

    void applyRay(const Ray& r) {
        if((area[r.x][r.y] == 'o') || (area[r.x][r.y] == '*')) {
            return;
        }
        char c;
        switch(r.angle) {
        case 45:
        case 225:
            c = '/';
            break;
        case 135:
        default:
            c = '\\';
        };
        if(area[r.x][r.y] == 'X') {
            return;
        }
        if((area[r.x][r.y] == '\\') && (c == '/')) {
            c = 'X';
        }
        else if((area[r.x][r.y] == '/') && (c == '\\')) {
            c = 'X';
        }
        area[r.x][r.y] = c;
    }

    void findFirstRay() {
#define POPULATE(a, b, c)                       \
        do {                                    \
            r.x = a;                            \
            r.y = b;                            \
            r.angle = c;                        \
        } while(0)
        Ray r;
        for(int i=0;i<ARENA_SIZE;++i) {
            // top
            if(area[0][i] == '/') {
                POPULATE(0, i, 225);
            }
            else if(area[0][i] == '\\') {
                POPULATE(0, i, 315);
            }
            // bottom
            else if(area[ARENA_SIZE-1][i] == '/') {
                POPULATE(ARENA_SIZE-1, i, 45);
            }
            else if(area[ARENA_SIZE-1][i] == '\\') {
                POPULATE(ARENA_SIZE-1, i, 135);
            }
            // left
            else if(area[i][0] == '/') {
                POPULATE(i, 0, 45);
            }
            else if(area[i][0] == '\\') {
                POPULATE(i, 0, 315);
            }
            // right
            else if(area[i][ARENA_SIZE-1] == '/') {
                POPULATE(i, ARENA_SIZE-1, 225);
            }
            else if(area[i][ARENA_SIZE-1] == '\\') {
                POPULATE(i, ARENA_SIZE-1, 135);
            }
        }
        Ray* r1 = new Ray;
        r1->x = r.x;
        r1->y = r.y;
        r1->angle = r.angle;
        rays.push_back(r1);
        first = r;
#undef POPULATE
    }
};


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RayOfLight <fileContainingTestVectors>\n");
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
        Arena ar;
        ar.populateArena(currentLine);
        ar.runSimulation();
        //ar.print();
        //printf("\n");
        ar.serialize();
    }
    fclose(fp);
    return 0;
}
