#include "Graph.hpp"

int main() {
    Graph g = Graph(15);
    g.initializeRandomGraph(105);
    g.print();

    Vertex vertexArray[2] = {0, 1};

    g.enumerateCyclesDFS();
}