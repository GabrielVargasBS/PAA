#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "Graph.hpp"
#include "Tests/Test.cpp"

#define NUM_TESTS 20
#define MAX_VERTEX 10

int main()
{
    for(int vertex = 3; vertex <= MAX_VERTEX; vertex++)
    {
        printf("\nVértices %d : \n", vertex);

        Test testPermutacao = Test(NUM_TESTS);
        Test testDFS = Test(NUM_TESTS);

        Graph graph = Graph(vertex);

        for(int i = 0; i < NUM_TESTS; i++)
        {
            srand(time(nullptr));
            int maxEdges = vertex*(vertex-1)/2;
            int edges = rand() % maxEdges;

            graph.initializeRandomNonDirectedGraph(edges);

            // Permutação
            auto startPermutation = high_resolution_clock::now();
            graph.enumerateCyclesPermutation();
            auto stopPermutation = high_resolution_clock::now();
            testPermutacao.addDuration(startPermutation, stopPermutation);
            testPermutacao.addMatrixAccess(graph.getMatrixAccessPermutation());

            // DFS
            auto startDFS = high_resolution_clock::now();
            graph.enumerateCyclesDFS();
            auto stopDFS = high_resolution_clock::now();
            testDFS.addDuration(startDFS, stopDFS);
            testDFS.addMatrixAccess(graph.getMatrixAccessDFS());
        }

        testPermutacao.printExecutionTime("Permutação  ");
        testPermutacao.printMatrixAccess("Permutação  ");
        testDFS.printExecutionTime("Caminhamento");
        testDFS.printMatrixAccess("Caminhamento");
    }

    return 0;
}
