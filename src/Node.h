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

/**
 * Lines that connect the bus stops
 */
struct Edge {
    int dest;   // Destination node
    double weight; // An integer weight
    string line;

};

/**
 * Struct only used for calculating Kruskal MST value
 */
struct EdgeKruskal {
    int src;    // Source node
    int dest;   // Destination node
    double weight; // An integer weight

    // For Kruskal's
    bool operator<(const EdgeKruskal &other) const {
        return weight < other.weight;
    }

    bool operator==(const EdgeKruskal &other) const {
        return ((src == other.src && dest == other.dest) ||
                (src == other.dest && dest == other.src)) &&
               weight == other.weight;
    }
};

/**
 * A Node represents a Bus Stop
 */
 struct Node {
    list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    double distance;
    int parent;  // previous node of the path
    bool visited;
    string code;  //unique code of the bus stop
    string local;
    string zone;
    Coordinates coordinates;
    int changesOfLine;  //used in dijkstraLine algorithm calculation
    map<string, pair<double, int>> lines; // used for dijkstraLine algorithm calculations
};


#endif //BUSNAVIGATIONPROGRAM_NODE_H
