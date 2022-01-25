#ifndef BUSNAVIGATIONPROGRAM_MENU_H
#define BUSNAVIGATIONPROGRAM_MENU_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Graph.h"

using namespace std;

class Menu {
    string directory;
    Graph graph;

public:
    Menu(string directory);
    Graph& getGraph();

    void createGraphStops();
    void createGraphLines();
    void createGraphLine(string line);

    static vector<string> split(string line, string delimeter);
};


#endif //BUSNAVIGATIONPROGRAM_MENU_H
