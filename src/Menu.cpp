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
        //graph.printNodes();
        clear();
        showMenu();
        option = readInputMenu();
        if (option == 1) {bestPathDijkstra();}
        else if (option == 2) {askSwapWalkDistance();}
        else if (option == 3) {askMSTPrim();}
        else if (option == 4) {askMSTKruskal();}
        else if (option == 5) {graph.printNodes();}

        if (option != 0) pressEnterToContinue();
    } while (option != 0);
}

/**
 * Waits for user to press enter to continue
 */
void Menu::pressEnterToContinue() {
    cout << "\n\tPress enter to continue \t" << endl;
    cin.ignore(10000, '\n');
    getchar();
}

void Menu::showMenu() {
    cout << "\n\t\t\t\t Bus Navigation Program " << endl;
    cout << "\tThe best app to help you find the path you are looking for!" << endl;
    cout << "\n\n\t1) Calcular trajeto de autocarro" << endl;
    cout << "\t2) Definir distância a andar" << endl;
    cout << "\t3) Obter o valor da MST usando Prim" << endl;
    cout << "\t4) Obter o valor da MST usando Kruskal" << endl;
    cout << "\t5) Imprimir Paragens (Teste) " << endl;
    cout << "\t0) Exit " << endl;
}

void Menu::showStopsOrLocation() {
    cout << "\n\n\t1) Indicar paragens de autocarro" << endl;
    cout << "\t2) Indicar coordenadas " << endl;
}

void Menu::showAlgorithmOptions() {
    cout << "\n\n\t1) Trajeto mais rápido" << endl;
    cout << "\t2) Trajeto com menos paragens" << endl;
    cout << "\t3) Trajeto com menos mudancas de linha " << endl;
    cout << "\t4) Outras opcões ..." << endl;
}

/**
 * Reads input from the user in the main menu
 * @return choice of the user
 */
int Menu::readInputMenu() {
    int chosenOption;
    bool notValid;
    do {
        cout << "\n   Enter option: ";
        cin >> chosenOption;
        notValid = chosenOption != 1 && chosenOption != 2 && chosenOption != 3 && chosenOption != 4 && chosenOption != 5 && chosenOption != 0 ;
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

int Menu::readInputStopsOrLocation() {
    int chosenOption;
    bool notValid;
    do {
        cout << "\n   Enter option: ";
        cin >> chosenOption;
        notValid = chosenOption != 1 && chosenOption != 2;
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

int Menu::readInputBestAlgorithm() {
    int chosenOption;
    bool notValid;
    do {
        cout << "\n   Enter option: ";
        cin >> chosenOption;
        notValid = chosenOption != 1 && chosenOption != 2 && chosenOption != 3;
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

/**
 * Reads integer from the user (General use)
 * @return value given by the user
 */
int Menu::readInt() {
    int x; bool fail;
    do {
        cin >> x;
        fail = cin.fail();
        if (fail)  {
            cout << "it failed \t" << endl;
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid Input Try again: \t" << endl;
        }
    } while (fail);
    return x;
}

double Menu::readDouble() {
    double x; bool fail;
    do {
        cin >> x;
        fail = cin.fail();
        if (fail)  {
            cout << "it failed \t" << endl;
            if (cin.eof()) {
                exit(0);
            }
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid Input Try again: \t" << endl;
        }
    } while (fail);
    return x;
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

int Menu::askStartEnd(string &stopBegin, string &stopEnd, Coordinates &cBegin, Coordinates &cEnd) {
    int option;
    showStopsOrLocation();
    option = readInputStopsOrLocation();
    if (option == 1) {
        cout << "\n\tIn which Bus Stop will your trip start at? "; stopBegin = readString();
        cout << "\tAnd where will it end? "; stopEnd = readString();
    } else {
        if (graph.getWalkingDistance() == 0) {
            cout << "If you don't want to walk, then, instead of giving such precisive coordinates, you should insert the code of the stop" << endl;
            return 3;
        }
        cout << "\n\tCoordinates of starting place" << endl;
        cout << "\tLatitude: "; cBegin.latitude = readDouble();
        cout << "\tLongitude: "; cBegin.longitude = readDouble();

        cout << "\n\tCoordinates of ending place" << endl;
        cout << "\tLatitude: "; cEnd.latitude = readDouble();
        cout << "\tLongitude: "; cEnd.longitude = readDouble();
    }
    return option;
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
    stack<int> path;
    int option, optionAlgorithm;
    double distance = -1.0;
    string stopBegin, stopEnd;
    Coordinates cBegin, cEnd;

    option = askStartEnd(stopBegin, stopEnd, cBegin, cEnd);
    if (option == 1) {
        showAlgorithmOptions();
        optionAlgorithm = readInputBestAlgorithm();

        if (optionAlgorithm == 1) {
            distance = graph.dijkstra(stopBegin, stopEnd);
        } else if (optionAlgorithm == 2) {
            distance = graph.bfs(stopBegin, stopEnd);
        } else if (optionAlgorithm == 3) {
            distance = graph.dijkstraLine(stopBegin, stopEnd);
        }

        if (distance != -1.0) {
            cout << "\tYou will have to travel " << distance << "km " << endl;
            if (optionAlgorithm != 3) {
                path = graph.getPathFromGraph(stopBegin, stopEnd);
                graph.printPath(path);
            } else {
                path = graph.getPathFromGraph(stopBegin, stopEnd);
                cout << "Its: " << path.size() <<  endl;
                graph.printPathLinesAlgorithm(path);
            }

        } else {
            cout << "\n\tNo path available" << endl;
        }



    } else if (option == 2) {
        graph.insertTemporaryNode(cBegin, true);
        graph.insertTemporaryNode(cEnd, false);

        showAlgorithmOptions();
        optionAlgorithm = readInputBestAlgorithm();

        if (optionAlgorithm == 1) {
            distance = graph.dijkstra("-start-", "-end-");
        } else if (optionAlgorithm == 2) {
            distance = graph.bfs("-start-", "-end-");
        } else if (optionAlgorithm == 3) {
            distance = graph.dijkstraLine("-start-", "-end-");
        }

        if (distance != -1.0) {
            cout << "\tYou will have to travel " << distance << "km " << endl;
            if (optionAlgorithm != 3) {
                path = graph.getPathFromGraph("-start-", "-end-");
                graph.printPath(path);
            } else {
                path = graph.getPathFromGraph("-start-", "-end-");
                graph.printPathLinesAlgorithm(path);
            }
        } else {
            cout << "\n\tOnly walking that far won't be enough" << endl;
        }
        graph.removeTemporaryNodes();



    } else {return;}
}


void Menu::askWalkingDistance() {
    double walkDist;
    cout << "\n\tSet a limit to how much you want to walk to/from a stop (kilometers): ";  walkDist = readDouble();
    graph.setWalkingDistance(walkDist);
}

void Menu::askSwapDistance() {
    double swapDist;
    cout << "\n\tSet a limit to how much you want to swap between stops (kilometers): ";  swapDist = readDouble();
    graph.setSwapDistance(swapDist);
}

void Menu::askSwapWalkDistance() {
    int option;
    cout << "\n\t1) Definir distância a andar até uma paragem" << endl;
    cout << "\t2) Definir distância a andar entre paragens (mudar de linha)" << endl;
    cout << "\n   Enter option: "; option = readInt();
    if (option == 1) askWalkingDistance();
    else if (option == 2) askSwapDistance();
}

void Menu::askMSTPrim() {
    string stop;
    cout << "\n\tSelect a Bus Stop to start to calculations: "; stop = readString();

    unordered_map<string, int> pos = graph.getPositions();
    try {
        int n = pos.at(stop);
        cout << "\n\tThe MST of this graph of stops is, according to Prim's Algorithm: " << graph.prim(n) << "km" << endl;
    } catch (out_of_range) {
        cout << "\n\tSorry, but there is no Bus Stop with that code" << endl;
    }

}

void Menu::askMSTKruskal() {
    cout << "\n\tThe MST of this graph of stops is, according to Kruskal's Algorithm: " << graph.kruskal();
}


