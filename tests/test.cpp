#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GraphsForTests.cpp"

using testing::Eq;

// We will have to change all this, but it's just to get a general idea
// Tests from the class exercises
TEST(test1, Prim) {
    cout << "Testing 'prim'" << endl;
    Graph graph1 = graph1Generator();
    Graph graph2 = graph2Generator();
    Graph graph3 = graph3Generator();
    Graph graph4 = graph4Generator();

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

TEST(test2, kruskal) {
    cout << "Testando 'kruskal'" << endl;

    Graph graph1 = graph1Generator();
    Graph graph2 = graph2Generator();
    Graph graph3 = graph3Generator();
    Graph graph4 = graph4Generator();

    cout << " graph1" << endl;
    EXPECT_EQ(27, graph1.kruskal());

    cout << " graph2" << endl;
    EXPECT_EQ(38, graph2.kruskal());

    cout << " graph3" << endl;
    EXPECT_EQ(22, graph3.kruskal());

    cout << " graph4" << endl;
    EXPECT_EQ(9, graph4.kruskal());
}

TEST(test3, Dijkstra) {
    cout << "Testando 'dijkstra_distance'" << endl;

    Graph graph1 = graph1Dijkstra();
    Graph graph2 = graph2Dijkstra();
    Graph graph3 = graph3Dijkstra();

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