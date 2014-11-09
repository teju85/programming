//
// Challenge name: Robot Movements
// Difficulty    : hard
// Link          : http://codeeval.com/open_challenges/56/
// Compile       : g++ -Wall -g -o UniquePaths UniquePaths.cpp
//

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;


/** A node in the graph */
typedef int Node;
/** All child nodes of a node in the graph */
typedef vector<Node> ChildNodes;
/** child-node iterator for a given node */
typedef ChildNodes::iterator Children;
/** the graph */
typedef vector<ChildNodes> Graph;


/**
 * @class NumUniqPaths paths.cpp
 * @brief Main class to solve this puzzle
 */
class NumUniqPaths {
public:
    /*
     * @brief Constructor
     * @param g dimension of the square grid
     */
    NumUniqPaths(int g): m_dim(g), m_num_paths(-1) {
        m_goal = _construct_node(m_dim-1, m_dim-1);
        _construct_graph();
    }

    /**
     * @brief Destructor
     */
    ~NumUniqPaths() {}

    /**
     * @brief get the number of unique paths
     * @return number of unique paths
     */
    int num_paths() {
        if(m_num_paths > 0) {
            return m_num_paths;
        }
        Node start(0);
        m_num_paths = _count_paths(start);
        return m_num_paths;
    }

private:
    /**
     * @brief Recursive function to count the number of unique paths
     * @param node current node
     * @return number of unique paths from this node to the goal node
     */
    int _count_paths(const Node& node) {
        int num = 0;
        Children itr;
        ChildNodes child = m_graf[node];
        _set_visited(node, true);
        for(itr=child.begin();itr!=child.end();++itr) {
            if(_is_goal(*itr)) {
                ++num;
                continue;
            }
            if(_is_visited(*itr)) {
                continue;
            }
            num += _count_paths(*itr);
        }
        _set_visited(node, false);
        return num;
    }

    /**
     * @brief Constructs the graph of the grid
     */
    void _construct_graph() {
        for(int i=0;i<m_dim;++i) {
            for(int j=0;j<m_dim;++j) {
                ChildNodes nodes;
                // up
                if(i > 0) {
                    Node n = _construct_node(i-1, j);
                    nodes.push_back(n);
                }
                // down
                if(i < m_dim-1) {
                    Node n = _construct_node(i+1, j);
                    nodes.push_back(n);
                }
                // left
                if(j > 0) {
                    Node n = _construct_node(i, j-1);
                    nodes.push_back(n);
                }
                // right
                if(j < m_dim-1) {
                    Node n = _construct_node(i, j+1);
                    nodes.push_back(n);
                }
                m_graf.push_back(nodes);
            }
        }
    }

    /**
     * @brief Constructs a node given its position
     * @param x x location
     * @param y y location
     * @return node
     */
    Node _construct_node(int x, int y) const {
        int pos = (x * m_dim) + y;
        return Node(pos);
    }

    /**
     * @brief Sets the 'visited'ness of a node
     * @param node the node
     * @param visited whether this node has been visited or not
     */
    void _set_visited(const Node& node, bool visited) {
        if(visited) {
            m_visited[node] = true;
        }
        else if(m_visited.find(node) != m_visited.end()) {
            m_visited.erase(node);
        }
    }

    /**
     * @brief Tells whether a node has been visited or not
     * @param node the node
     * @return true if it has been visited, else false
     */
    bool _is_visited(const Node& node) const {
        return (m_visited.find(node) != m_visited.end());
    }

    /**
     * @brief Tells whether the input node is a goal node or not
     * @param node input node
     * @return true if it is the goal node, else false
     */
    bool _is_goal(const Node& node) const {
        return (node == m_goal);
    }

    /** dimension of the square grid */
    int m_dim;
    /** number of unique paths */
    int m_num_paths;
    /** graph of all nodes */
    Graph m_graf;
    /** list of visited nodes in the graph till now */
    map<Node, bool> m_visited;
    /** goal node */
    Node m_goal;
};


int main(int argc, char** argv) {
    NumUniqPaths calc(4);
    printf("%d\n", calc.num_paths());
    return 0;
}
