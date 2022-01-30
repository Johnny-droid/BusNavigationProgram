#ifndef BUSNAVIGATIONPROGRAM_NODE_H
#define BUSNAVIGATIONPROGRAM_NODE_H

#include <list>
#include <string>
#include <map>

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

/*
// For Kruskal's
int src;
bool operator<(const Edge &other) const {
    return weight < other.weight;
}

bool operator==(const Edge &other) const {
    return ((src == other.src && dest == other.dest) ||
            (src == other.dest && dest == other.src)) &&
           weight == other.weight;
}
 */

 struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    double distance;
    int parent;
    bool visited;
    string code;
    string local;
    string zone;
    Coordinates coordinates;
    int changesOfLine;
    map<string, pair<double, int>> lines; //lines {weight, and parent}
};


#endif //BUSNAVIGATIONPROGRAM_NODE_H
