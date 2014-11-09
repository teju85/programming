//
// Challenge name: Bus Network
// Difficulty    : hard
// Link          : https://www.codeeval.com/open_challenges/134/
// Compile       : g++ -Wall -g -o BusNetwork BusNetwork.cpp
//

#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Route: public vector<int> {
public:
    Route(): vector<int>(), nodeMap() {}
    Route(const Route& r): vector<int>(r), nodeMap(r.nodeMap) {}
    ~Route() {}
    void push_back(int val) {
        vector<int>::push_back(val);
        nodeMap[val] = true;
    }
    bool hasNode(int id) {
        return (nodeMap.find(id) != nodeMap.end());
    }
    int findNodePos(int node) const {
        int len = (int) size();
        for(int i=0;i<len;++i) {
            if(at(i) == node) {
                return i;
            }
        }
        return -1;
    }
    int costBetweenPoints(int pos1, int pos2) const {
        int del = (pos2 > pos1)? (pos2 - pos1) : (pos1 - pos2);
        return (del * 7);
    }
private:
    map<int, bool> nodeMap;
};

typedef map<int, Route>  Routes;
typedef map<int, vector<int> >  Nodes;

class BusNetwork {
public:
    BusNetwork(int s, int e, FILE* fp): routes(), nodes(), rAdj(), start(s), end(e), visited() {
        populateMap(fp);
    }
    ~BusNetwork() {}
    bool isEmpty() const { return routes.empty(); }
    int findMinTime() {
        int min = 0x7fffffff;
        vector<int>& nod = nodes[start];
        for(vector<int>::const_iterator itr=nod.begin();itr!=nod.end();++itr) {
            int pos = findNodePos(start, *itr);
            int c = _minCost(pos, *itr, 0);
            if(c < min) {
                min = c;
            }
        }
        return min;
    }
private:
    int _minCost(int nodePos, int rId, int cost) {
        int min = 0x7fffffff;
        if(visited[rId]) {
            return min;
        }
        Route& r = routes[rId];
        if((nodePos < 0) || (nodePos >= (int)r.size())) {
            return min;
        }
        if(r.hasNode(end)) {
            int endPos = r.findNodePos(end);
            min = cost + r.costBetweenPoints(nodePos, endPos);
        }
        visited[rId] = true;
        set<int>& adjR = rAdj[rId];
        for(set<int>::const_iterator itr=adjR.begin();itr!=adjR.end();++itr) {
            if(visited[*itr]) {
                continue;
            }
            Route& r2 = routes[*itr];
            vector<int> ptsPos;
            findIntersections(nodePos, rId, *itr, ptsPos);
            for(vector<int>::const_iterator pos=ptsPos.begin();pos!=ptsPos.end();++pos) {
                int rc = cost + 12 + r2.costBetweenPoints(nodePos, *pos);
                int r2Pos = r2.findNodePos(r[*pos]);
                int c = _minCost(r2Pos, *itr, rc);
                if(c < min) {
                    min = c;
                }
            }
        }
        visited[rId] = false;
        return min;
    }
    bool hasNode(int node, int rId) {
        return (routes[rId].hasNode(node));
    }
    bool hasEndNode(int rId) {
        return hasNode(end, rId);
    }
    int findNodePos(int node, int rId) {
        return routes[rId].findNodePos(node);
    }
    void findIntersections(int nodePos, int r1, int r2, vector<int>& ptsPos) {
        Route& rout1 = routes[r1];
        Route& rout2 = routes[r2];
        for(int i=nodePos-1;i>=0;--i) {
            if(rout2.hasNode(rout1[i])) {
                ptsPos.push_back(i);
            }
        }
        int size = (int) rout1.size();
        for(int i=nodePos+1;i<size;++i) {
            if(rout2.hasNode(rout1[i])) {
                ptsPos.push_back(i);
            }
        }
    }
    void addNode(int id, int rId) {
        routes[rId].push_back(id);
        if(nodes.find(id) == nodes.end()) {
            nodes[id] = vector<int>();
        }
        nodes[id].push_back(rId);
    }
    void readRoute(FILE* fp, int rId) {
        routes[rId] = Route();
        rAdj[rId] = set<int>();
        visited[rId] = false;
        while(true) {
            int stop;
            if(fscanf(fp, "=[%d", &stop) == 1) {
                addNode(stop, rId);
            }
            else if(fscanf(fp, ",%d", &stop) == 1) {
                addNode(stop, rId);
            }
            else {
                return;
            }
        }
    }
    void populateMap(FILE* fp) {
        while(true) {
            int rId = -1;
            if(fscanf(fp, "); R%d", &rId) == 1) {
            }
            else if(fscanf(fp, "]; R%d", &rId) == 1) {
            }
            else {
                for(Nodes::const_iterator itr=nodes.begin();itr!=nodes.end();++itr) {
                    const vector<int>& rs = itr->second;
                    int len = (int)rs.size();
                    for(int i=0;i<len;++i) {
                        for(int j=i+1;j<len;++j) {
                            rAdj[rs[i]].insert(rs[j]);
                            rAdj[rs[j]].insert(rs[i]);
                        }
                    }
                }
                return;
            }
            readRoute(fp, rId);
        }
    }
    Routes routes;
    Nodes nodes;
    map<int, set<int> > rAdj;
    int start;
    int end;
    map<int, bool> visited;
};

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: BusNetwork <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        int start, end;
        start = end = -1;
        if(fscanf(fp, "(%d,%d", &start, &end) == 2) {
        }
        else if(fscanf(fp, "\n(%d,%d", &start, &end) == 2) {
        }
        else {
            continue;
        }
        BusNetwork net(start, end, fp);
        if(net.isEmpty()) {
            continue;
        }
        int min = net.findMinTime();
        if(min == 0x7fffffff) {
            printf("None\n");
        }
        else {
            printf("%d\n", min);
        }
    }
    fclose(fp);
    return 0;
}
