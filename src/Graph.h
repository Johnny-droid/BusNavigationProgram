#pragma once
#ifndef BUSNAVIGATIONPROGRAM_GRAPH_H
#include <list>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include "Node.h"
#include "MinHeap.h"
#include "DisjointSets.h"

using namespace std;

class Graph {
    int n;              // Graph size (vertices are numbered from 1 to n)
    double walkingDistance = 0.001; //km
    double swapDistance = 0.0;
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, int> positions;


public:
    // Constructor: nr nodes and direction (default: directed)
    Graph(int nodes = 0, bool dir = true);
    Graph(vector<Node> nodes, unordered_map<string, int> positions, bool dir = true);
    vector<Node>& getNodes();
    double getWalkingDistance();
    double getSwapDistance();
    unordered_map<string, int> getPositions();
    void setWalkingDistance(double walkingDist);
    void setSwapDistance(double swapDist);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, string line);
    void addEdge(int src, int dest, string line);
    void addEdge(int src, int dest, double weight = 1.0);
    double calculateDistance(Coordinates c1, Coordinates c2);
    double calculateDistance(int src, int dest);
    int calculateChangesOfLine(map<string, pair<double, int>> lines, int numPrevChangesOfLines, string newLine);
    double calculateWeightDijkstraLine(int min, double edgeWeight, string newLine);

    long double prim(int r);
    double kruskal();

    double bfs(string src, string dest);
    double bfs(int a, int b);
    double dijkstra(string src, string dest);
    double dijkstra(int a, int b);
    double dijkstraLine(string src, string dest);
    double dijkstraLine(int a, int b);

    stack<int> getPathFromGraph(string src, string dest);
    stack<int> getPathFromGraph(int a, int b);

    void printPath(stack<int> path);
    void printPathLinesAlgorithm(stack<int> path);
    void printNodes();
    void insertTemporaryNode(Coordinates c, bool startType);
    void removeTemporaryNodes();
};


#endif //BUSNAVIGATIONPROGRAM_GRAPH_H
