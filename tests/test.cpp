#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Menu.h"
#include "GraphsForTests.h"

using testing::Eq;

//Desenhos dos graphicos:
// https://moodle.up.pt/pluginfile.php/155550/mod_label/intro/aed2122_p11.pdf?time=1642503159552



/**
 * Tests if dijkstra can determine the distance between adjacent nodes.
 * This test is done on the small map.
 */
TEST(SmallMapDistances, travelling2stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(0, graphS1.dijkstra("U", "U"));
    EXPECT_EQ(18247, round(graphS1.dijkstra("A", "B") * 100000));
    EXPECT_EQ(10627, round(graphS1.dijkstra("R", "E") * 100000));
    EXPECT_EQ(44369, round(graphS1.dijkstra("F", "E") * 100000));
    EXPECT_EQ(6325, round(graphS1.dijkstra("G", "F") * 100000));
    EXPECT_EQ(12792, round(graphS1.dijkstra("G", "H") * 100000));
    EXPECT_EQ(20804, round(graphS1.dijkstra("P", "J") * 100000));
    EXPECT_EQ(14622, round(graphS1.dijkstra("J", "I") * 100000));
    EXPECT_EQ(16414, round(graphS1.dijkstra("I", "B") * 100000));
}
/**
 * Tests if dijkstra can determine the distance two nodes with a path that is 2 edges long.
 * This test is done on the small map.
 */
TEST(SmallMapDistances, travelling3stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(40673, round(graphS1.dijkstra("C", "E") * 100000));
    EXPECT_EQ(35427, round(graphS1.dijkstra("P", "I") * 100000));
    EXPECT_EQ(31036, round(graphS1.dijkstra("J", "B") * 100000));
}
/**
 * Tests if dijkstra can determine the distance two nodes with a path that is 3 edges long.
 * This test is done on the small map.
 */
TEST(SmallMapDistances, travelling4stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(50170, round(graphS1.dijkstra("G", "J") * 100000));
    EXPECT_EQ(51840, round(graphS1.dijkstra("P", "B") * 100000));
}
/**
 * Tests if dijkstra can determine the distance two nodes with a path that is 4 edges long.
 * This test is done on the small map.
 */
TEST(SmallMapDistances, travelling5stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(74113, round(graphS1.dijkstra("R", "H") * 100000));
}

bool compareStacks(stack<int> stack1, stack<int> stack2, Graph& g1) {
    //cout << "-----------------" << endl;
    //cout << "  Test  |  Real  " << endl;
    //if (stack1.size() != stack2.size()) return false;
    vector<Node> nodes = g1.getNodes();
    while (!stack1.empty() || !stack2.empty()) {
        //cout << "\t" << nodes[stack1.top()].code << "   |   " <<  nodes[stack2.top()].code << endl;
        if (stack1.top() != stack2.top()) return false;
        stack1.pop();
        stack2.pop();
    }
    return true;
}
/**
 * Tests if dijkstra can determine the best path between two nodes.
 * This test is done on the small map.
 */
TEST(SmallMapPaths, itineraries) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    stack<int> testStack;
    int n;
    unordered_map<string, int> positions = graphS1.getPositions();

    //poe todas as positions por ordem contraria

    n = positions["E"]; testStack.push(n);
    graphS1.dijkstra("E", "E");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("E", "E"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["B"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    graphS1.dijkstra("A", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("A", "B"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["L"]; testStack.push(n);
    n = positions["N"]; testStack.push(n);
    graphS1.dijkstra("N", "L");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("N", "L"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["T"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    graphS1.dijkstra("O", "T");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("O", "T"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["B"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    n = positions["L"]; testStack.push(n);
    graphS1.dijkstra("L", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("L", "B"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["L"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    n = positions["B"]; testStack.push(n);
    graphS1.dijkstra("B", "L");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("B", "L"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["O"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    graphS1.dijkstra("A", "O");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("A", "O"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["A"]; testStack.push(n);
    n = positions["L"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    graphS1.dijkstra("O", "A");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("O", "A"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["B"]; testStack.push(n);
    n = positions["I"]; testStack.push(n);
    n = positions["J"]; testStack.push(n);
    n = positions["P"]; testStack.push(n);
    graphS1.dijkstra("P", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("P", "B"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["P"]; testStack.push(n);
    n = positions["K"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    n = positions["B"]; testStack.push(n);
    graphS1.dijkstra("B", "P");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("B", "P"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["B"]; testStack.push(n);
    n = positions["I"]; testStack.push(n);
    n = positions["J"]; testStack.push(n);
    n = positions["K"]; testStack.push(n);
    graphS1.dijkstra("K", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("K", "B"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["K"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    n = positions["B"]; testStack.push(n);
    graphS1.dijkstra("B", "K");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("B", "K"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["K"]; testStack.push(n);
    n = positions["P"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["N"]; testStack.push(n);
    graphS1.dijkstra("N", "K");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("N", "K"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["N"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["K"]; testStack.push(n);
    graphS1.dijkstra("K", "N");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("K", "N"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["G"]; testStack.push(n);
    n = positions["F"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    graphS1.dijkstra("O", "G");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("O", "G"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["Q"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["F"]; testStack.push(n);
    n = positions["G"]; testStack.push(n);
    graphS1.dijkstra("G", "Q");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("G", "Q"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["C"]; testStack.push(n);
    n = positions["D"]; testStack.push(n);
    n = positions["E"]; testStack.push(n);
    n = positions["F"]; testStack.push(n);
    graphS1.dijkstra("F", "C");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("F", "C"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["K"]; testStack.push(n);
    n = positions["P"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["T"]; testStack.push(n);
    graphS1.dijkstra("T", "K");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("T", "K"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["B"]; testStack.push(n);
    n = positions["I"]; testStack.push(n);
    n = positions["D"]; testStack.push(n);
    n = positions["R"]; testStack.push(n);
    n = positions["S"]; testStack.push(n);
    graphS1.dijkstra("S", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("S", "B"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["S"]; testStack.push(n);
    n = positions["R"]; testStack.push(n);
    n = positions["D"]; testStack.push(n);
    n = positions["C"]; testStack.push(n);
    n = positions["B"]; testStack.push(n);
    graphS1.dijkstra("B", "S");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("B", "S"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["Q"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["P"]; testStack.push(n);
    n = positions["K"]; testStack.push(n);
    n = positions["E"]; testStack.push(n);
    n = positions["R"]; testStack.push(n);
    graphS1.dijkstra("R", "Q");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("R", "Q"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["R"]; testStack.push(n);
    n = positions["E"]; testStack.push(n);
    n = positions["K"]; testStack.push(n);
    n = positions["P"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["T"]; testStack.push(n);
    graphS1.dijkstra("T", "R");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("T", "R"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["U"]; testStack.push(n);
    n = positions["H"]; testStack.push(n);
    n = positions["G"]; testStack.push(n);
    n = positions["F"]; testStack.push(n);
    n = positions["E"]; testStack.push(n);
    n = positions["R"]; testStack.push(n);
    n = positions["S"]; testStack.push(n);
    graphS1.dijkstra("S", "U");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("S", "U"), graphS1));
    while (!testStack.empty()) testStack.pop();

    n = positions["T"]; testStack.push(n);
    n = positions["O"]; testStack.push(n);
    n = positions["M"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    n = positions["B"]; testStack.push(n);
    n = positions["C"]; testStack.push(n);
    graphS1.dijkstra("C", "T");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.getPathFromGraph("C", "T"), graphS1));
    while (!testStack.empty()) testStack.pop();
}

TEST(test1, Dijkstra) {
    std::cout << "Testing 'dijkstra'" << std::endl;

    Graph graph1 = GraphsForTests::graph1Dijkstra();
    Graph graph2 = GraphsForTests::graph2Dijkstra();
    Graph graph3 = GraphsForTests::graph3Dijkstra();

    cout << "  . graph1" << endl;
    EXPECT_EQ(9,graph1.dijkstra(1, 2));
    EXPECT_EQ(9,graph1.dijkstra(2, 1));
    EXPECT_EQ(8,graph1.dijkstra(1, 5));
    EXPECT_EQ(8,graph1.dijkstra(5, 1));
    EXPECT_EQ(11,graph1.dijkstra(1, 3));
    EXPECT_EQ(11,graph1.dijkstra(3, 1));
    EXPECT_EQ(9,graph1.dijkstra(1, 7));
    EXPECT_EQ(9,graph1.dijkstra(7, 1));
    EXPECT_EQ(8,graph1.dijkstra(4, 3));
    EXPECT_EQ(8,graph1.dijkstra(3, 4));
    EXPECT_EQ(6,graph1.dijkstra(4, 2));
    EXPECT_EQ(6,graph1.dijkstra(2, 4));

    cout << "  . graph2" << endl;
    EXPECT_EQ(18,graph2.dijkstra(1, 9));
    EXPECT_EQ(18,graph2.dijkstra(9, 1));
    EXPECT_EQ(24,graph2.dijkstra(1, 3));
    EXPECT_EQ(24,graph2.dijkstra(3, 1));
    EXPECT_EQ(11,graph2.dijkstra(2, 3));
    EXPECT_EQ(11,graph2.dijkstra(3, 2));
    EXPECT_EQ(8,graph2.dijkstra(6, 8));
    EXPECT_EQ(8,graph2.dijkstra(8, 6));

    cout << "  . graph3" << endl;
    EXPECT_EQ(-1, graph3.dijkstra(8, 11));
    EXPECT_EQ(22, graph3.dijkstra(11, 8));
    EXPECT_EQ(12, graph3.dijkstra(3, 8));
    EXPECT_EQ(6, graph3.dijkstra(8, 3));
    EXPECT_EQ(2, graph3.dijkstra(10, 5));
    EXPECT_EQ(23, graph3.dijkstra(5, 10));
    EXPECT_EQ(4, graph3.dijkstra(10, 4));
    EXPECT_EQ(-1, graph3.dijkstra(6, 11));
    EXPECT_EQ(-1, graph3.dijkstra(1, 11));
}

/*
TEST(test4, PrintNodes) {
    cout << "Testing PrintNodes" << endl;
    Menu menu("dataset");
    menu.getGraph().printNodes();
}
*/


TEST(test2, Prim) {
    cout << "Testing 'prim'" << endl;
    Graph graph1 = GraphsForTests::graph1Generator();
    Graph graph2 = GraphsForTests::graph2Generator();
    Graph graph3 = GraphsForTests::graph3Generator();
    Graph graph4 = GraphsForTests::graph4Generator();

    EXPECT_EQ(27, graph1.prim(1));
    EXPECT_EQ(27, graph1.prim(2));
    EXPECT_EQ(27, graph1.prim(3));
    EXPECT_EQ(27, graph1.prim(4));
    EXPECT_EQ(27, graph1.prim(5));
    EXPECT_EQ(27, graph1.prim(6));
    EXPECT_EQ(27, graph1.prim(7));

    cout << "  . graph2" << endl;
    EXPECT_EQ(38, graph2.prim(1));
    EXPECT_EQ(38, graph2.prim(5));
    EXPECT_EQ(38, graph2.prim(9));
    // parab??ns encontraste o coment??rio secreto :D
    cout << "  . graph3" << endl;
    EXPECT_EQ(22, graph3.prim(1));
    EXPECT_EQ(22, graph3.prim(2));
    EXPECT_EQ(22, graph3.prim(3));
    EXPECT_EQ(22, graph3.prim(9));
    EXPECT_EQ(22, graph3.prim(10));
    EXPECT_EQ(22, graph3.prim(11));

    cout << "  . graph4" << endl;
    EXPECT_EQ(9, graph4.prim(1));
    EXPECT_EQ(9, graph4.prim(2));
    EXPECT_EQ(9, graph4.prim(3));
    EXPECT_EQ(9, graph4.prim(4));
}

TEST(test3, kruskal) {
    cout << "Testando 'kruskal'" << endl;

    Graph graph1 = GraphsForTests::graph1Generator();
    Graph graph2 = GraphsForTests::graph2Generator();
    Graph graph3 = GraphsForTests::graph3Generator();
    Graph graph4 = GraphsForTests::graph4Generator();

    cout << " graph1" << endl;
    EXPECT_EQ(27, graph1.kruskal());

    cout << " graph2" << endl;
    EXPECT_EQ(38, graph2.kruskal());

    cout << " graph3" << endl;
    EXPECT_EQ(22, graph3.kruskal());

    cout << " graph4" << endl;
    EXPECT_EQ(9, graph4.kruskal());
}

