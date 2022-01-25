#pragma once
#ifndef BUSNAVIGATIONPROGRAM_GRAPH_H
#include <list>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include "Node.h"
#include "MinHeap.h"

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, int> positions;


public:
    // Constructor: nr nodes and direction (default: directed)
    Graph(int nodes = 0, bool dir = true);
    Graph(vector<Node> nodes, unordered_map<string, int> positions, bool dir = true);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, string line);
    void addEdge(int src, int dest, string line);
    void addEdge(int src, int dest, int weight = 1);
    int calculateDistance(int src, int dest);

    int prim(int v);
    int kruskal();
    int dijkstra(int a, int b);
    list<int> dijkstra_path(int a, int b);

    void printNodes();
};


#endif //BUSNAVIGATIONPROGRAM_GRAPH_H
