#include "Graph.hpp"

int main() {
    Graph g = Graph(10);
    g.initializeRandomGraph(20);
    g.print();

    Vertex vertexArray[2] = {0, 1};

    bool hasCycle = g.hasCycle(vertexArray , 2);
    printf("hasCycle = %d", hasCycle);
}