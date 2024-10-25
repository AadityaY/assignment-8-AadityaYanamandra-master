#include <iostream>
#include <vector>
#include "../code_1/Graph.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    Graph graph;
    graph.addVertex("Chicago");
    graph.addVertex("NYC");
    graph.addVertex("Boston");

    graph.addEdge("Chicago", "Boston");
    graph.addEdge("NYC", "Boston");
    graph.displayEdges();
    return 0;
}
