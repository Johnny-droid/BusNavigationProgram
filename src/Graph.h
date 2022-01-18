#ifndef BUSNAVIGATIONPROGRAM_GRAPH_H

#include <list>
#include <vector>
#include "Node.h"

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    int prim(int v);
    int kruskal();
    int dijkstra(int startNode, int endNode);
};


#endif //BUSNAVIGATIONPROGRAM_GRAPH_H
