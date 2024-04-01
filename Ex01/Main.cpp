#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "Graph.hpp"
#include "Tests/Test.cpp"

#define MAX_VERTEX 10
#define MAX_EDGES 45

#define NUM_TESTS 10

int main()
{
    printf("\nCENARIO A: Grafos completos, variando número de vértices\n");
    
    for(int vertex = 3; vertex <= MAX_VERTEX; vertex++)
    {
        printf("\nVértices %d : \n", vertex);

        Test testPermutacao = Test(NUM_TESTS);
        Test testDFS = Test(NUM_TESTS);

        for(int i = 0; i < NUM_TESTS; i++)
        {
            Graph graph = Graph(vertex);
            int edges = (vertex)*(vertex-1)/2;
            graph.initializeRandomNonDirectedGraph(edges);

            // Permutação
            auto startPermutation = high_resolution_clock::now();
            graph.enumerateCyclesPermutation();
            auto stopPermutation = high_resolution_clock::now();
            testPermutacao.addDuration(startPermutation, stopPermutation);

            // DFS
            auto startDFS = high_resolution_clock::now();
            graph.enumerateCyclesDFS();
            auto stopDFS = high_resolution_clock::now();
            testDFS.addDuration(startDFS, stopDFS);
        }

        testPermutacao.printExecutionTime("Permutação  ");
        testDFS.printExecutionTime("Caminhamento");
    }

    printf("\n\nCENARIO B: Grafos de 10 vértices, variando número de arestas\n");

    for(int edges = 0; edges <= MAX_EDGES; edges+=5)
    {
        printf("\nArestas %d : \n", edges);

        Test testPermutacao = Test(NUM_TESTS);
        Test testDFS = Test(NUM_TESTS);

        for(int i = 0; i < NUM_TESTS; i++)
        {
            Graph graph = Graph(MAX_VERTEX);
            graph.initializeRandomNonDirectedGraph(edges);

            // Permutação
            auto startPermutation = high_resolution_clock::now();
            graph.enumerateCyclesPermutation();
            auto stopPermutation = high_resolution_clock::now();
            testPermutacao.addDuration(startPermutation, stopPermutation);

            // DFS
            auto startDFS = high_resolution_clock::now();
            graph.enumerateCyclesDFS();
            auto stopDFS = high_resolution_clock::now();
            testDFS.addDuration(startDFS, stopDFS);
        }

        testPermutacao.printExecutionTime("Permutação  ");
        testDFS.printExecutionTime("Caminhamento");
    }

    return 0;
}
