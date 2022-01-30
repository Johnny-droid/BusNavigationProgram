#include "Graph.h"
#include "float.h"
#include "set"

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {}

Graph::Graph(vector<Node> nodes, unordered_map<string, int> positions, bool dir) {
    this->n = nodes.size() - 1;
    this->hasDir = dir;
    this->positions = positions;
    this->nodes = nodes;
}

vector<Node>& Graph::getNodes() {
    return nodes;
}

double Graph::getWalkingDistance() {
    return this->walkingDistance;
}

double Graph::getSwapDistance() {
    return this->swapDistance;
}

unordered_map<string, int> Graph::getPositions() {
    return this->positions;
}

void Graph::setWalkingDistance(double walkingDist) {
    this->walkingDistance = walkingDist;
}

void Graph::setSwapDistance(double swapDist) {
    //remover todos as edges walking "antigas"
    for (int i = 1; i < nodes.size(); i++) {
        auto it = nodes[i].adj.begin();
        while (it != nodes[i].adj.end()) {
            if (it->line == "walk") {
                it = nodes[i].adj.erase(it);
            } else {
                it++;
            }
        }
    }

    this->swapDistance = swapDist;

    // colocar as respetivas arestas com a nova distância
    for (int src = 1; src < nodes.size()-1; src++) {
        for (int dest = src + 1; dest < nodes.size(); dest++) {
            if (calculateDistance(src, dest) <= swapDistance) {
                addEdge(src, dest, "walk");
                addEdge(dest, src, "walk");
            }
        }
    }
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
    if (src<1 || src>nodes.size() || dest<1 || dest>nodes.size()) return;
    nodes[src].adj.push_back({dest, calculateDistance(src, dest), line});
    if (!hasDir) nodes[dest].adj.push_back({dest, calculateDistance(src, dest), line});
}

void Graph::addEdge(int src, int dest, double weight) {
    if (src<1 || src>nodes.size() || dest<1 || dest>nodes.size()) return;
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


long double Graph::prim(int r) {
    long double sum = 0;
    MinHeap<int, double> heap(nodes.size(), -1);
    for (int i = 1; i < nodes.size(); i++) {
        heap.insert(i, DBL_MAX/2);
        nodes[i].distance = DBL_MAX/2;
        nodes[i].parent = 0;
    }
    heap.decreaseKey(r, 0);
    nodes[r].distance = 0;
    while (heap.getSize() != 0) {
        int u = heap.removeMin();
        sum += (long double) nodes[u].distance;
        for (Edge edge : nodes[u].adj) {
            int w = edge.dest;
            if (heap.hasKey(w) && edge.weight < nodes[w].distance) {
                heap.decreaseKey(w, edge.weight);
                nodes[w].distance = edge.weight;
                nodes[w].parent = u;
            }
        }
    }
    return sum;
}

long double Graph::kruskal() {

    DisjointSets<int> disjoinSets;
    set<EdgeKruskal> edges;
    long double total = 0;

    for (int i = 1; i <= n; i++) {
        disjoinSets.makeSet(i);
    }

    for (int i = 1 ; i < nodes.size(); i++) {
        for (Edge edge : nodes[i].adj) {
            edges.insert({i, edge.dest, edge.weight});
        }
    }

    for (EdgeKruskal y : edges) {
        if (disjoinSets.find(y.dest) != disjoinSets.find(y.src)) {
            disjoinSets.unite(y.dest, y.src);
            total += (long double) y.weight;
        }
    }

    return total;
}

double Graph::bfs(string src, string dest) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        return bfs(start, end);
    } catch (out_of_range) {
        cout << "\tThere aren't any stops with that code" << endl;
        return -1;
    }
}

double Graph::bfs(int a, int b) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(a);
    nodes[a].visited = true;
    nodes[a].distance = 0;
    nodes[a].parent = a;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].distance = nodes[u].distance + e.weight;
                nodes[w].parent = u;
                q.push(w);
                nodes[w].visited = true;

                if (w == b) {return nodes[w].distance;}
            }
        }
    }

    return -1.0;
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

double Graph::dijkstraLine(string src, string dest) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        return dijkstraLine(start, end);
    } catch (out_of_range) {
        cout << "\tThere aren't any stops with that code" << endl;
        return -1;
    }
}


double Graph::dijkstraLine(int a, int b) {
    MinHeap<int, int> heap(nodes.size(), -1.0);
    for (int i = 1; i < nodes.size(); i++) { // i < n
        nodes[i].changesOfLine = INT32_MAX;
        nodes[i].lines = map<string, pair<double, int>>();
        heap.insert(i, INT32_MAX);
        nodes[i].distance = DBL_MAX;
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }
    heap.decreaseKey(a, 0);
    nodes[a].distance = 0.0;
    nodes[a].parent = a;
    nodes[a].changesOfLine = 0;

    while (heap.getSize() != 0) {
        int min = heap.removeMin();
        nodes[min].visited = true;
        for (Edge edge : nodes[min].adj) {
            int newChangesOfLine = calculateChangesOfLine(nodes[min].lines, nodes[min].changesOfLine, edge.line);
            double newWeight = calculateWeightDijkstraLine(min, edge.weight, edge.line);

            if (!nodes[edge.dest].visited && nodes[edge.dest].changesOfLine > newChangesOfLine) {
                heap.decreaseKey(edge.dest, newChangesOfLine);
                nodes[edge.dest].changesOfLine = newChangesOfLine;
                nodes[edge.dest].lines.clear();
                nodes[edge.dest].lines[edge.line] = {newWeight, min};

            } else if (!nodes[edge.dest].visited && nodes[edge.dest].changesOfLine == newChangesOfLine) {
                if (nodes[edge.dest].lines.find(edge.line) != nodes[edge.dest].lines.end()) {
                    double prevWeight = nodes[edge.dest].lines.at(edge.line).first;
                    if (prevWeight > newWeight) {
                        nodes[edge.dest].lines[edge.line] = {newWeight, min};
                    }
                } else {
                    nodes[edge.dest].lines[edge.line] = {newWeight, min};
                }

            }
        }
    }

    if (nodes[b].lines.empty()) return -1;
    int parent, lastNode = b; string line;
    double distance, minWeight = DBL_MAX;
    for (auto it = nodes[b].lines.begin(); it != nodes[b].lines.end(); it++) {
        if (it->second.first < minWeight) {
            minWeight = it->second.first;
            parent = it->second.second;
            nodes[lastNode].parent = it->second.second;
            line = it->first;
        }
    }
    distance = minWeight;
    lastNode = parent;
    while (!nodes[lastNode].lines.empty()) {
        try {
            nodes[lastNode].lines.at(line);
            parent = nodes[lastNode].lines[line].second;
            minWeight = nodes[lastNode].lines[line].first;
            nodes[lastNode].parent = parent;
            nodes[lastNode].lines.clear();
            nodes[lastNode].lines[line] = {minWeight, parent};
            lastNode = parent; //updates

        } catch (out_of_range) {
            minWeight = DBL_MAX;
            for (auto it = nodes[lastNode].lines.begin(); it != nodes[lastNode].lines.end(); it++) {
                if (it->second.first < minWeight) {
                    minWeight = it->second.first;
                    nodes[lastNode].parent = it->second.second;
                    line = it->first;
                    parent = it->second.second;
                }
            }
            nodes[lastNode].lines.clear();
            nodes[lastNode].lines[line] = {minWeight, parent};  //leaves only 1 line
            lastNode = parent; //updates
        }
    }

    return distance;
}

int Graph::calculateChangesOfLine(map<string, pair<double, int>> lines, int numPrevChangesOfLines, string newLine) {
    try {
        lines.at(newLine);
        return numPrevChangesOfLines;
    } catch (out_of_range) {
        return numPrevChangesOfLines + 1;
    }
}

double Graph::calculateWeightDijkstraLine(int min, double edgeWeight, string newLine) {
    if (nodes[min].lines.empty()) return edgeWeight;
    double minWeight;
    try {
        nodes[min].lines.at(newLine);
        return nodes[min].lines[newLine].first + edgeWeight;
    } catch (out_of_range) {
        minWeight = DBL_MAX;
        for (auto it = nodes[min].lines.begin(); it != nodes[min].lines.end(); it++) {
            if (it->second.first < minWeight) {
                minWeight = it->second.first;
            }
        }
        return minWeight + edgeWeight;
    }
}


stack<int> Graph::getPathFromGraph(string src, string dest) {
    int start, end;
    try {
        start = positions.at(src);
        end = positions.at(dest);
        return getPathFromGraph(start, end);
    } catch (out_of_range) {
        cout << "Something went wrong in print path..." << endl;
        return stack<int>();
    }
}


stack<int> Graph::getPathFromGraph(int a, int b) {
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


void Graph::printPath(stack<int> path) {
    int i; double distance; bool found = false;
    string line = "";
    cout << "\n";
    while (!path.empty()) {
        i = path.top();
        path.pop();

        if (path.empty()) break;

        for (Edge edge : nodes[i].adj) {
            if (edge.line == line && edge.dest == path.top()) {
                distance = edge.weight;
                found = true;
                break;
            }
        }

        if (!found) {
            for (Edge edge : nodes[i].adj) {
                if (edge.dest == path.top()) {
                    distance = edge.weight;
                    line = edge.line;
                    break;
                }
            }
        }
        found = false;
        cout << "\t" << nodes[i].code << " -----  line:" << line << " | distance: " << distance << "km ----> " << nodes[path.top()].code << endl;
    }
}

void Graph::printPathLinesAlgorithm(stack<int> path) {
    int i; double distance; bool found = false;
    string line;
    cout << "\n";
    while (!path.empty()) {
        i = path.top();
        path.pop();

        if (path.empty()) break;

        line = nodes[path.top()].lines.begin()->first;
        for (Edge edge : nodes[i].adj) {
            if (edge.dest == path.top() && edge.line == line) {
                distance = edge.weight;
                break;
            }
        }
        cout << "\t" << nodes[i].code << " -----  line:" << line << " | distance: " << distance << "km ----> " << nodes[path.top()].code << endl;
    }
}


//Used only for tests
void Graph::printNodes() {
    for (int i = 1; i < nodes.size(); i++) {
        cout << "\n\tCode: " << nodes[i].code << "\tPosition: " << positions[nodes[i].code] << "\tLocal: " << nodes[i].local << endl;
        int j = 1;
        for (Edge edge : nodes[i].adj) {
            cout << "\t\t" << j << " Dest: " << nodes[edge.dest].code << "\tDistance: " << edge.weight << " km\t Line: " << edge.line << endl;
            j++;
        }
    }
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
                addEdge(node.code, nodes[i].code, "walk");
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
                addEdge(nodes[i].code, node.code, "walk");
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
        if (nodes[i].code == "-end-") continue;
        auto it = nodes[i].adj.begin();
        while (it != nodes[i].adj.end()) {
            if (it->dest == positions["-end-"]) {
                it = nodes[i].adj.erase(it);
            } else {
                it++;
            }
        }
    }
    nodes.erase(nodes.begin() + positions["-end-"]);
    positions.erase("-end-");
}



