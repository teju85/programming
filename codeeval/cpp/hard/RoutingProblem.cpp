//
// Challenge name: Routing Problem
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/129/
// Compile       : g++ -Wall -g -o RoutingProblem RoutingProblem.cpp
//

#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;


struct Interface {
    Interface(): ip(0), mask(0) {
    }

    Interface(const Interface& i): ip(i.ip), mask(i.mask) {
    }

    ~Interface() {
    }

    bool read(FILE* fp) {
        unsigned int a, b, c, d, s;
        if(fscanf(fp, ": ['%u.%u.%u.%u/%u", &a, &b, &c, &d, &s) != 5) {
            if(fscanf(fp, "', '%u.%u.%u.%u/%u", &a, &b, &c, &d, &s) != 5) {
                return false;
            }
        }
        ip = (a << 24) | (b << 16) | (c << 8) | d;
        mask = (1 << (32 - s)) - 1;
        mask = ~mask;
        return true;
    }

    bool sameSubnet(const Interface& i) const {
        return ((ip & mask) == (i.ip & i.mask));
    }

    void print() const {
        printf("  %u.%u.%u.%u %u.%u.%u.%u\n",
               (ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff, ip&0xff,
               (mask>>24)&0xff, (mask>>16)&0xff, (mask>>8)&0xff, mask&0xff);
    }

    unsigned int ip;
    unsigned int mask;
};


struct Host {
    Host(): id(0), ips() {
    }

    ~Host() {
    }

    Host(const Host& h): id(h.id), ips(h.ips) {
    }

    bool read(FILE* fp) {
        if(fscanf(fp, "{%d", &id) != 1) {
            int ff = fscanf(fp, "], %d", &id);
            if(ff != 1) {
                return false;
            }
        }
        while(!feof(fp)) {
            Interface iface;
            if(!iface.read(fp)) {
                break;
            }
            ips.push_back(iface);
        }
        return true;
    }

    bool sameSubnet(const Host& h) const {
        int l1 = (int)ips.size();
        int l2 = (int)h.ips.size();
        for(int i=0;i<l1;++i) {
            for(int j=0;j<l2;++j) {
                if(ips[i].sameSubnet(h.ips[j])) {
                    return true;
                }
            }
        }
        return false;
    }

    void print() const {
        printf("Host: %d\n", id);
        for(vector<Interface>::const_iterator i=ips.begin();i!=ips.end();++i) {
            i->print();
        }
    }

    int id;
    vector<Interface> ips;
};


struct Graph {
    void read(FILE* fp) {
        while(true) {
            Host h;
            if(!h.read(fp)) {
                break;
            }
            hosts.push_back(h);
        }
        char tmp;
        fscanf(fp, "%c", &tmp);
    }

    void construct() {
        for(vector<Host>::const_iterator i=hosts.begin();i!=hosts.end();++i) {
            vector<int> neigh;
            for(vector<Host>::const_iterator j=hosts.begin();j!=hosts.end();++j) {
                if(i->sameSubnet(*j)) {
                    neigh.push_back(j->id);
                }
                adj[i->id] = neigh;
            }
        }
    }

    void print() const {
        for(vector<Host>::const_iterator i=hosts.begin();i!=hosts.end();++i) {
            i->print();
        }
        printf("Adjacency\n");
        for(map<int,vector<int> >::const_iterator i=adj.begin();i!=adj.end();++i) {
            printf("  %d: ", i->first);
            for(vector<int>::const_iterator j=i->second.begin();j!=i->second.end();++j) {
                printf(" %d", *j);
            }
            printf("\n");
        }
    }

private:
    friend class BFS;
    vector<Host> hosts;
    map<int, vector<int> > adj;
};


struct VecSorter {
    bool operator()(const vector<int>& a, const vector<int>& b) {
        int len = (int)a.size();
        for(int i=len-1;i>=0;--i) {
            if(a[i] < b[i]) return true;
            if(a[i] > b[i]) return false;
        }
        return true;
    }
};


struct BFS {
    void findAllPaths(int s, int e, Graph* _g) {
        g = _g;
        start = s;
        end = e;
        frontier.push(start);
        weights[start] = 0;
        bfs();
        backtrack();
        printPaths();
    }

private:
    void printPaths() const {
        bool first = true;
        for(vector<vector<int> >::const_iterator i=paths.begin();i!=paths.end();++i) {
            if(first) {
                first = false;
            }
            else {
                printf(", ");
            }
            printVec(*i);
        }
        if(first) {
            printf("No connection");
        }
        printf("\n");
    }

    void printVec(const vector<int>& v) const {
        printf("[");
        bool first = true;
        int len = (int)v.size();
        for(int j=len-1;j>=0;--j) {
            if(first) {
                first = false;
            }
            else {
                printf(", ");
            }
            printf("%d", v[j]);
        }
        printf("]");
    }

    void backtrack() {
        vector<int> p;
        p.push_back(end);
        _generatePaths(end, p);
        sort(paths.begin(), paths.end(), VecSorter());
    }

    void _generatePaths(int node, vector<int>& currPath) {
        if(node == start) {
            paths.push_back(currPath);
            return;
        }
        vector<int>& pred = parent[node];
        for(vector<int>::const_iterator i=pred.begin();i!=pred.end();++i) {
            vector<int> p;
            for(vector<int>::const_iterator j=currPath.begin();j!=currPath.end();++j) {
                p.push_back(*j);
            }
            p.push_back(*i);
            _generatePaths(*i, p);
        }
    }

    void bfs() {
        while(!frontier.empty()) {
            int node = frontier.front();
            frontier.pop();
            if(node == end) {
                continue;
            }
            if(isVisited(node)) {
                continue;
            }
            visited.insert(node);
            addNeighbors(node);
        }
    }

    void addNeighbors(int node) {
        vector<int>& neigh = g->adj[node];
        for(vector<int>::const_iterator i=neigh.begin();i!=neigh.end();++i) {
            if(!isVisited(*i)) {
                if(weights.find(*i) == weights.end()) {
                    weights[*i] = ((int)g->hosts.size()) * 2;
                }
                int cost = weights[node] + 1;
                if(weights[*i] > cost) {
                    weights[*i] = cost;
                    parent[*i] = vector<int>();
                    updateParent(*i, node);
                }
                else if(weights[*i] == cost) {
                    updateParent(*i, node);
                }
            }
        }
    }

    void updateParent(int node, int pred) {
        if(parent.find(node) == parent.end()) {
            parent[node] = vector<int>();
        }
        parent[node].push_back(pred);
        frontier.push(node);
    }

    bool isVisited(int node) const {
        return (visited.find(node) != visited.end());
    }

    int start;
    int end;
    Graph* g;
    map<int, vector<int> > parent;
    set<int> visited;
    queue<int> frontier;
    vector<vector<int> > paths;
    map<int, int> weights;
};


int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: RoutingProblem <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    Graph g;
    g.read(fp);
    g.construct();
    //g.print();
    while(!feof(fp)) {
        int start, end;
        if(fscanf(fp, "%d%d", &start, &end) != 2) {
            continue;
        }
        //printf("%d %d\n", start, end);
        BFS b;
        b.findAllPaths(start, end, &g);
    }
    fclose(fp);
    return 0;
}
