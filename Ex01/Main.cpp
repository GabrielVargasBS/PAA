#include "Graph.hpp"

int main() {
    Graph g = Graph(10);
    g.initializeRandomGraph(2);
    g.print();

    g.enumerateCyclesPermutation();

    printf("\n\n\n");

    g.enumerateCyclesDFS();
}