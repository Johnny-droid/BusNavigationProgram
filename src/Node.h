#ifndef BUSNAVIGATIONPROGRAM_NODE_H
#define BUSNAVIGATIONPROGRAM_NODE_H

#include <list>
#include <string>

using namespace std;

struct Edge {
    int dest;   // Destination node
    int weight; // An integer weight
    string line;
};

 struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    int distance;
    int parent;
    bool visited;
};


#endif //BUSNAVIGATIONPROGRAM_NODE_H
