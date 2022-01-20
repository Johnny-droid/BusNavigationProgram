#include "Graph.h"


Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {}

void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

int Graph::prim(int v) {
    return 0;
}

int Graph::kruskal() {
    return 0;
}

int Graph::dijkstra(int a, int b) {
    MinHeap<int, int> heap(nodes.size(), -1);
    for (int i = 1; i < nodes.size(); i++) { // i < n
        heap.insert(i, INT32_MAX);
        nodes[i].distance = INT32_MAX;
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }
    heap.decreaseKey(a, 0);
    nodes[a].distance = 0;
    nodes[a].parent = a;

    while (heap.getSize() != 0) {
        int min = heap.removeMin();
        nodes[min].visited = true;
        for (Edge edge : nodes[min].adj) {
            int newWeight = edge.weight + nodes[min].distance;
            if (!nodes[edge.dest].visited && nodes[edge.dest].distance > newWeight) {
                heap.decreaseKey(edge.dest, newWeight);
                nodes[edge.dest].distance = newWeight;
                nodes[edge.dest].parent = min;
            }
        }
    }

    return nodes[b].distance != INT32_MAX ? nodes[b].distance : -1;
}

list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;

    dijkstra(a, b);

    int lastNode = b;
    int parentNode = nodes[lastNode].parent;
    if (parentNode == -1) return path;
    path.push_front(lastNode);

    while (lastNode != parentNode) {
        path.push_front(parentNode);
        lastNode = parentNode;
        parentNode = nodes[parentNode].parent;
    }
    return path;
}
