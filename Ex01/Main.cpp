#include "Graph.hpp"

int main() {
    Graph g = Graph(5);
    g.initializeRandomGraph(10);
    g.print();

    int count1 = 0;
    g.enumerateCyclesPermutation(&count1);

    int count2 = 0;
    g.enumerateCyclesDFS(&count2);

    printf("\nCount Permutation = %d", count1);
    printf("\nCount DFS = %d", count2);
    printf("\n");
}