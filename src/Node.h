#ifndef BUSNAVIGATIONPROGRAM_NODE_H
#define BUSNAVIGATIONPROGRAM_NODE_H

#include <list>
#include <string>

using namespace std;

struct Coordinates {
    double latitude;
    double longitude;
};

struct Edge {
    int dest;   // Destination node
    double weight; // An integer weight
    string line;
};

 struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    double distance;
    int parent;
    bool visited;
    string code;
    string local;
    string zone;
    Coordinates coordinates;
    vector<string> lines;
};


#endif //BUSNAVIGATIONPROGRAM_NODE_H
