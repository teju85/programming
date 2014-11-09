//
// Challenge name: Grid Walk
// Difficulty    : hard
// Link          : http://www.codeeval.com/open_challenges/60/
// Compile       : g++ -Wall -g -o GridWalk GridWalk.cpp
//

#include <stdio.h>
#include <set>
#include <vector>

#define THRESH 19

using namespace std;

struct Coord {
    int x;
    int y;
    Coord(): x(0), y(0) {}
    Coord(const Coord& in): x(in.x), y(in.y) {}
    Coord(int _x, int _y): x(_x), y(_y) {}
    Coord& operator=(const Coord& in) {
        x = in.x;
        y = in.y;
        return *this;
    }
    ~Coord() {}
    bool operator==(const Coord& in) const {
        return ((x == in.x) && (y == in.y));
    }
    bool isAccessible() const {
        int c = (sumOfDigits(x) + sumOfDigits(y));
        return (c <= THRESH);
    }
    void print() const {
        printf("x=%d, y=%d\n", x, y);
    }
private:
    int sumOfDigits(int d) const {
        int a = (d < 0)? -d : d;
        int sum = 0;
        while(a) {
            sum += (a % 10);
            a /= 10;
        }
        return sum;
    }
};


#define ABS(a)  ((unsigned int)((a < 0)? -a : a))
struct CoordCompare {
    bool operator() (const Coord& lhs, const Coord& rhs) const {
        return (convert(lhs.x, lhs.y) < convert(rhs.x, rhs.y));
    }
private:
    unsigned long long int convert(int x, int y) const {
        unsigned long long int a = ((unsigned long long int) x) & 0xffffffff;
        unsigned long long int b = ((unsigned long long int) y) & 0xffffffff;
        return ((a << 32) | b);
    }
};


typedef set<Coord, CoordCompare>  Grid;
typedef vector<Coord>             GridList;


void workOnPoint(int x, int y, Grid& g, GridList& gl) {
    Coord n(x, y);
    if(!n.isAccessible()) {
        return;
    }
    if(g.find(n) == g.end()) {
        //n.print();
        g.insert(n);
        gl.push_back(n);
    }
}

void addNextPointsToBeVisited(Coord& c, Grid& g, GridList& gl) {
    workOnPoint(c.x+1, c.y, g, gl);
    workOnPoint(c.x, c.y+1, g, gl);
    workOnPoint(c.x-1, c.y, g, gl);
    workOnPoint(c.x, c.y-1, g, gl);
}

int main(int argc, char** argv) {
    Grid g;
    GridList gl;
    Coord zero(0, 0);
    g.insert(zero);
    gl.push_back(zero);
    while(!gl.empty()) {
        Coord c = gl.front();
        gl.erase(gl.begin());
        //printf("Working on ... ");
        //c.print();
        addNextPointsToBeVisited(c, g, gl);
        //printf("list=%d, set=%d\n", (int)gl.size(), (int)g.size());
    }
    printf("%d\n", (int)g.size());
    return 0;
}
