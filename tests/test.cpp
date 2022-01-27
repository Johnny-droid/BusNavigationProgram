#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Menu.h"
#include "GraphsForTests.h"

using testing::Eq;

//Desenhos dos graphicos:
// https://moodle.up.pt/pluginfile.php/155550/mod_label/intro/aed2122_p11.pdf?time=1642503159552




TEST(SmallMapDistances, travelling1stop) {
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

TEST(SmallMapDistances, travelling2stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(40673, round(graphS1.dijkstra("C", "E") * 100000));
    EXPECT_EQ(35427, round(graphS1.dijkstra("P", "I") * 100000));
    EXPECT_EQ(31036, round(graphS1.dijkstra("J", "B") * 100000));
}

TEST(SmallMapDistances, travelling3stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(50170, round(graphS1.dijkstra("G", "J") * 100000));
    EXPECT_EQ(51840, round(graphS1.dijkstra("P", "B") * 100000));
}

TEST(SmallMapDistances, travelling4stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(74113, round(graphS1.dijkstra("R", "H") * 100000));
}

TEST(SmallMapPaths, travelling4stops) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    EXPECT_EQ(74113, round(graphS1.dijkstra("R", "H") * 100000));
}

bool compareStacks(stack<int> stack1, stack<int> stack2) {
    if (stack1.size() != stack2.size()) return false;
    while (!stack1.empty()) {
        if (stack1.top() != stack2.top()) return false;
        stack1.pop();
        stack2.pop();
    }
    return true;
}

TEST(CopyMapDistances, travelling1stop) {
    Menu menu("dataset-small");
    Graph graphS1 = menu.getGraph();
    //graphS1.printNodes();
    stack<int> testStack;
    int n;
    unordered_map<string, int> positions = graphS1.getPositions();
    n = positions["B"]; testStack.push(n);
    n = positions["A"]; testStack.push(n);
    //poe todas as positions por ordem contraria
    graphS1.dijkstra("A", "B");
    EXPECT_EQ(true, compareStacks(testStack, graphS1.dijkstra_path("A", "B")));
}


/*
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
}*/
/*
TEST(test1, Dijkstra_path) {
    cout << "Testing 'dijkstra_path'" << endl;

    // For these examples there is only one shortest path, so we can compare
    // directly, but on a general case, for accepting any shortest path,
    // the verification would need to take that into account

    Graph graph1 = GraphsForTests::graph1Dijkstra();
    Graph graph2 = GraphsForTests::graph2Dijkstra();
    Graph graph3 = GraphsForTests::graph3Dijkstra();

    list<int> ans;

    cout << "  . graph1" << endl;

    ans = {1,4,5,2}; EXPECT_EQ(ans,graph1.dijkstra_path(1, 2));
    ans = {2,5,4,1}; EXPECT_EQ(ans,graph1.dijkstra_path(2, 1));
    ans = {1,4,5}; EXPECT_EQ(ans,graph1.dijkstra_path(1, 5));
    ans = {5,4,1}; EXPECT_EQ(ans,graph1.dijkstra_path(5, 1));
    ans = {1,4,6,3}; EXPECT_EQ(ans,graph1.dijkstra_path(1, 3));
    ans = {3,6,4,1}; EXPECT_EQ(ans,graph1.dijkstra_path(3, 1));
    ans = {1,4,6,7}; EXPECT_EQ(ans,graph1.dijkstra_path(1, 7));
    ans = {7,6,4,1}; EXPECT_EQ(ans,graph1.dijkstra_path(7, 1));
    ans = {4,6,3}; EXPECT_EQ(ans,graph1.dijkstra_path(4, 3));
    ans = {3,6,4}; EXPECT_EQ(ans,graph1.dijkstra_path(3, 4));
    ans = {4,5,2}; EXPECT_EQ(ans,graph1.dijkstra_path(4, 2));
    ans = {2,5,4}; EXPECT_EQ(ans,graph1.dijkstra_path(2, 4));

    cout << "  . graph2" << endl;
    ans = {1,5,6,9}; EXPECT_EQ(ans,graph2.dijkstra_path(1, 9));
    ans = {9,6,5,1}; EXPECT_EQ(ans,graph2.dijkstra_path(9, 1));
    ans = {1,5,6,3}; EXPECT_EQ(ans,graph2.dijkstra_path(1, 3));
    ans = {3,6,5,1}; EXPECT_EQ(ans,graph2.dijkstra_path(3, 1));
    ans = {2,6,3}; EXPECT_EQ(ans,graph2.dijkstra_path(2, 3));
    ans = {3,6,2}; EXPECT_EQ(ans,graph2.dijkstra_path(3, 2));
    ans = {6,5,8}; EXPECT_EQ(ans,graph2.dijkstra_path(6, 8));
    ans = {8,5,6}; EXPECT_EQ(ans,graph2.dijkstra_path(8, 6));

    cout << "  . graph3" << endl;
    ans = {}; EXPECT_EQ(ans,graph3.dijkstra_path(8, 11));
    ans = {11,6,4,3,2,1,7,8}; EXPECT_EQ(ans,graph3.dijkstra_path(11, 8));
    ans = {3,2,1,7,8}; EXPECT_EQ(ans,graph3.dijkstra_path(3, 8));
    ans = {8,4,3}; EXPECT_EQ(ans,graph3.dijkstra_path(8, 3));
    ans = {10,5}; EXPECT_EQ(ans,graph3.dijkstra_path(10, 5));
    ans = {5,4,3,2,1,7,9,10}; EXPECT_EQ(ans,graph3.dijkstra_path(5, 10));
    ans = {10,6,4}; EXPECT_EQ(ans,graph3.dijkstra_path(10, 4));
    ans = {}; EXPECT_EQ(ans,graph3.dijkstra_path(6, 11));
    ans = {}; EXPECT_EQ(ans,graph3.dijkstra_path(1, 11));

}
*/
/*
TEST(test4, PrintNodes) {
    cout << "Testing PrintNodes" << endl;
    Menu menu("dataset");
    menu.getGraph().printNodes();
}
*/

/*
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
    // parabéns encontraste o comentário secreto :D
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
*/
