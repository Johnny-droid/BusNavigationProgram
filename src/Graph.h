#pragma once
#ifndef BUSNAVIGATIONPROGRAM_GRAPH_H
#include <list>
#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include "Node.h"
#include "MinHeap.h"

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    int walkingDistance = 0;
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, int> positions;



public:
    // Constructor: nr nodes and direction (default: directed)
    Graph(int nodes = 0, bool dir = true);
    Graph(vector<Node> nodes, unordered_map<string, int> positions, bool dir = true);
    void setWalkingDistance(int walkingDistance);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, string line);
    void addEdge(int src, int dest, string line);
    void addEdge(int src, int dest, int weight = 1);
    int calculateDistance(Coordinates c1, Coordinates c2);
    int calculateDistance(int src, int dest);




    int prim(int v);
    int kruskal();
    int dijkstra(string src, string dest);
    int dijkstra(int a, int b);
    void dijkstra_pathPrint(string src, string dest);
    void dijkstra_pathPrint(int a, int b);

    void printNodes();

    void insertTemporaryNode(Coordinates c, bool startType);
    void removeTemporaryNodes();
private:
    bool existsEdgeLine(int node, string line);
};


#endif //BUSNAVIGATIONPROGRAM_GRAPH_H
