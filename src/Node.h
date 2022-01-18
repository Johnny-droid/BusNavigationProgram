#ifndef BUSNAVIGATIONPROGRAM_NODE_H
#define BUSNAVIGATIONPROGRAM_NODE_H

#include <list>

using namespace std;

struct Edge {
    int dest;   // Destination node
    int weight; // An integer weight
};

 struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    int distance;
    int parent;
};


#endif //BUSNAVIGATIONPROGRAM_NODE_H
