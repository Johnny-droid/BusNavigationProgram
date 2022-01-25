#include "Menu.h"

Menu::Menu(string directory) {
    this->directory = directory;
    createGraphStops();
    createGraphLines();
}

void Menu::createGraphStops() {
    ifstream fileStops;
    string line;
    vector<Node> nodes;
    unordered_map<string, int> positions;
    nodes.push_back({});

    fileStops.open( "../" + directory + "/stops.csv");
    if (!fileStops.is_open()) {
        cout << "Stops file not found!" << endl;
    } else {
        getline(fileStops,line);
        while (getline(fileStops, line)) {
            if (line.empty()) continue;
            vector<string> elements = split(line, ",");
            Node stop;
            stop.code = elements[0];
            stop.local = elements[1];
            stop.zone = elements[2];
            stop.coordinates = {stod(elements[3]) , stod(elements[4])};
            nodes.push_back(stop);
            positions[elements[0]] = nodes.size() - 1;
        }
    }
    fileStops.close();

    Graph graph1(nodes, positions);
    this->graph = graph1;
}

void Menu::createGraphLines() {
    ifstream fileLines;
    string str;

    fileLines.open("../" + directory + "/lines.csv");
    if (fileLines.is_open()) {
        getline(fileLines, str);
        while (getline(fileLines, str)) {
            if (str.empty()) continue;
            vector<string> elements = split(str, ",");
            createGraphLine(elements[0]);
        }
    } else {
        cout << "Lines.csv file not found! " << endl;
    }

    fileLines.close();
}

void Menu::createGraphLine(string line) {
    ifstream fileLine;
    string str1, str2;

    for (int a = 0; a < 2; a++) {
        fileLine.open("../" + directory + "/line_" + line + "_" + to_string(a) + ".csv");
        if (fileLine.is_open()) {
            getline(fileLine, str1); //ignore first line
            getline(fileLine, str1);
            while (getline(fileLine, str2)) {
                if (str2.empty()) continue;
                graph.addEdge(str1, str2, line);
                str1 = str2;
            }
        } else {
            cout << "line_" + line + "_" + to_string(a) + ".csv file not found! " << endl;
        }
        fileLine.close();
    }
}











vector<string> Menu::split(string line, string delimeter) {
    vector<string> v;

    while (line.length() != 0) {
        int pos = line.find_first_of(delimeter);
        if (pos == line.npos) {
            v.push_back(line);
            break;
        }
        string subStr = line.substr(0, pos);
        v.push_back(subStr);
        line = line.substr(pos + 1);
    }

    return v;
}

Graph &Menu::getGraph() {
    return this->graph;
}



