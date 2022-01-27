#include "Graph.h"
#include "float.h"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {}

Graph::Graph(vector<Node> nodes, unordered_map<string, int> positions, bool dir) {
    this->n = nodes.size() - 1;
    this->hasDir = dir;
    this->positions = positions;
    this->nodes = nodes;
}

double Graph::getWalkingDistance() {
    return this->walkingDistance;
}

unordered_map<string, int> Graph::getPositions() {
    return this->positions;
}

void Graph::setWalkingDistance(double walkingDistance) {
    removeTemporaryNodes();
    // talvez remover todos as edges walking
    this->walkingDistance = walkingDistance;
    // colocar as respetivas arestas com a nova distância

}


void Graph::addEdge(string src, string dest, string line) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        addEdge(start, end, line);
    } catch (out_of_range) {
        cout << "Failed to add an edge" << endl;
    }
}

void Graph::addEdge(int src, int dest, string line) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, calculateDistance(src, dest), line});
    if (!hasDir) nodes[dest].adj.push_back({dest, calculateDistance(src, dest), line});
}

void Graph::addEdge(int src, int dest, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

double Graph::calculateDistance(int src, int dest) {
    Coordinates c1 = nodes[src].coordinates;
    Coordinates c2 = nodes[dest].coordinates;
    return calculateDistance(c1, c2);
}

double Graph::calculateDistance(Coordinates c1, Coordinates c2) {
    double dLat = (c2.latitude - c1.latitude) * M_PI / 180.0;
    double dLon = (c2.longitude - c1.longitude) * M_PI / 180.0;
    double lat1 = c1.latitude * M_PI / 180.0;
    double lat2 = c2.latitude * M_PI / 180.0;
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


int Graph::prim(int v) {
    return 0;
}

int Graph::kruskal() {
    return 0;
}

double Graph::dijkstra(string src, string dest) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        return dijkstra(start, end);
    } catch (out_of_range) {
        cout << "\tThere aren't any stops with that code" << endl;
        return -1;
    }
}


double Graph::dijkstra(int a, int b) {
    MinHeap<int, double> heap(nodes.size(), -1.0);
    for (int i = 1; i < nodes.size(); i++) { // i < n
        heap.insert(i, DBL_MAX);
        nodes[i].distance = DBL_MAX;
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }
    heap.decreaseKey(a, 0);
    nodes[a].distance = 0.0;
    nodes[a].parent = a;

    while (heap.getSize() != 0) {
        int min = heap.removeMin();
        nodes[min].visited = true;
        for (Edge edge : nodes[min].adj) {
            double newWeight = edge.weight + nodes[min].distance;
            if (!nodes[edge.dest].visited && nodes[edge.dest].distance > newWeight) {
                heap.decreaseKey(edge.dest, newWeight);
                nodes[edge.dest].distance = newWeight;
                nodes[edge.dest].parent = min;
            }
        }
    }

    return nodes[b].distance != DBL_MAX ? nodes[b].distance : -1;
}

stack<int> Graph::dijkstra_path(string src, string dest) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        return dijkstra_path(start, end);
    } catch (out_of_range) {
        cout << "Something went wrong in print path" << endl;
        return stack<int>();
    }
}



stack<int> Graph::dijkstra_path(int a, int b) {
    stack<int> path;

    int lastNode = b;
    int parentNode = nodes[lastNode].parent;
    if (parentNode == -1) return {};
    path.push(lastNode);

    while (lastNode != parentNode) {
        path.push(parentNode);
        lastNode = parentNode;
        parentNode = nodes[parentNode].parent;
    }

    return path;
}


void Graph::dijkstra_pathPrint(stack<int> path) {
    cout << "\n";
    int i;
    double distance;
    string line = "";
    while (!path.empty()) {
        i = path.top();
        path.pop();

        if (path.empty()) break;

        if (existsEdgeLine(i, line)) {
            for (Edge edge : nodes[i].adj) {
                if (edge.line == line) {
                    distance = edge.weight;
                    break;
                }
            }
        } else {
            for (Edge edge : nodes[i].adj) {
                if (edge.dest == path.top()) {
                    distance = edge.weight;
                    line = edge.line;
                    break;
                }
            }
        }
        cout << "\t" << nodes[i].code << " -----  line:" << line << " | distance: " << distance << "km ----> " << nodes[path.top()].code << endl;
    }
}

//Used only for tests
void Graph::printNodes() {
    for (int i = 1; i < nodes.size(); i++) {
        cout << "Code :" << nodes[i].code << "\tPosition: " << positions[nodes[i].code] << "\tLocal: " << nodes[i].local << endl;
        int j = 1;
        for (Edge edge : nodes[i].adj) {
            cout << j << " Dest: " << nodes[edge.dest].code << "\tDistance: " << edge.weight << " km\t Line: " << edge.line << endl;
            j++;
        }
    }
}

bool Graph::existsEdgeLine(int node, string line) {
    for (Edge edge : nodes[node].adj) {
        if (edge.line == line) {
            return true;
        }
    }
    return false;
}

void Graph::insertTemporaryNode(Coordinates c, bool startType) {
    if (walkingDistance <= 0) return;

    Node node;
    node.coordinates = c;
    if (startType) {
        node.code = "-start-";
        try {
            positions.at(node.code);
            cout << "There is another starting point. Development error." << endl;
            return;
        } catch (out_of_range) {
            nodes.push_back(node);
            positions[node.code] = nodes.size() - 1;
        }
        for (int i = 1; i < nodes.size()-1; i++) {
            if (calculateDistance(c, nodes[i].coordinates) <= walkingDistance) {
                addEdge(nodes.size() - 1, i, "walk");
            }
        }
    } else {
        node.code = "-end-";
        try {
            positions.at(node.code);
            cout << "There is another ending point. Development error." << endl;
            return;
        } catch (out_of_range) {
            nodes.push_back(node);
            positions[node.code] = nodes.size() - 1;
        }
        for (int i = 1; i < nodes.size()-1; i++) {
            if (calculateDistance(c, nodes[i].coordinates) <= walkingDistance) {
                addEdge(i, nodes.size() - 1, "walk");
            }
        }
    }

}

void Graph::removeTemporaryNodes() {
    //remove -start-
    nodes.erase(nodes.begin() + positions["-start-"]);
    positions.erase("-start-");

    //remove -end-
    for (int i = 1; i < nodes.size(); i++) {
        auto it = nodes[i].adj.begin();
        while (it != nodes[i].adj.end()) {
            if (it->dest == positions["-end-"]) {
                nodes[i].adj.erase(it);
            } else {
                it++;
            }
        }
    }
    nodes.erase(nodes.begin() + positions["-end-"]);
    positions.erase("-end-");
}












