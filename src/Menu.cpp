#include "Menu.h"

Menu::Menu(string directory) {
    this->directory = directory;
    createGraphStops();
    createGraphLines();
}

Graph &Menu::getGraph() {
    return this->graph;
}


void Menu::run() {
    int option;
    do {
        clear();
        showMenu();
        option = readInputMenu();
        if (option == 1) {bestPathDijkstra();}
    } while (option != 0);
}

void Menu::showMenu() {
    cout << "\n\t\t\t\t Bus Navigation Program " << endl;
    cout << "\tThe best app to help you find the path you are looking for" << endl;
    cout << "\n\n\t1) Caminho mais rápido de autocarro" << endl;
    cout << "\t2) Outras opções... " << endl;
    cout << "\t0) Exit " << endl;
}

/**
 * Reads input from the user in the main menu
 * @return choice of the user
 */
int Menu::readInputMenu() {
    // gets the option number
    int chosenOption;
    bool notValid;
    do {
        cout << "\n   Enter option: ";
        cin >> chosenOption;
        notValid = chosenOption != 1 && chosenOption != 2 && chosenOption != 0 ;
        if ( notValid || cin.fail()) {
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "\t\tInvalid input!\n";
        }
    } while (notValid);
    cin.ignore(100000, '\n');
    return chosenOption;
}



/**
 * It clears the console by calling system()
 * (It might have problems in Clion, but it works well in the terminal)
 */
void Menu::clear() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

string Menu::readString() {
    string str; bool fail;
    // para conseguir ler um nome com mais do que uma palavra
    do {
        getline(cin, str);
        fail = cin.fail();
        if (fail)  {
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cout << "Invalid Input Try again: \t" << endl;
        }
    } while (fail);
    return str;
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

void Menu::bestPathDijkstra() {
    int distance;
    string begin, end;
    cout << "\n\tIn which Bus Stop will your trip start at? "; begin = readString();
    cout << "\tAnd where will it end? "; end = readString();
    distance = graph.dijkstra(begin, end);
    if (distance == -1) {
        cout << "\tI'm sorry, but there aren't stops with that code." << endl;
    } else {
        cout << "\tYou will have to travel " << distance << "m " << endl;
        graph.dijkstra_pathPrint(begin, end);
    }
}







