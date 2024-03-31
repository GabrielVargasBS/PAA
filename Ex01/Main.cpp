#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "Graph.hpp"

int main()
{
    // Graph graph = Graph(4);
    // graph.initializeRandomGraph(4);

    // // Encontrar ciclos
    // graph.enumerateCyclesPermutation();
    // graph.enumerateCyclesDFS();

    // // Obtém os ciclos encontrados
    // const vector<vector<Vertex>> &cyclesDFS = graph.getCyclesDFS();
    // const vector<vector<Vertex>> &cyclesPermutation = graph.getCyclesPermutation();

    // // Mostrar ciclos encontrados
    // graph.printCycles(cyclesDFS);
    // graph.printCycles(cyclesPermutation);

    // // Mostra ciclos iguais encontrados
    // int equalCyclesCount = graph.findEqualCycles();
    // printf("\nCiclos iguais encontrados: %d\n", equalCyclesCount);


    // LOOP para gerar testes
    // CENARIO A1: Grafos completos, variando número de vértices de 3 até limite
    printf("\nCENARIO A1: Grafos completos, variando número de vértices [Permutação]\n");
    for(int i = 3; i < 16; i++) {

        printf("\nVértices = %2d ", i);

        Graph graph = Graph(i);
        int edges = (i)*(i-1)/2;
        graph.initializeRandomGraph(edges);

        auto start = high_resolution_clock::now();
        graph.enumerateCyclesPermutation();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        auto seconds = duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto microseconds = duration_cast<std::chrono::microseconds>(duration);

        cout << "-> duração: "
            << seconds.count() << " segundos, "
            << microseconds.count() << " microssegundos." << endl;
    }

    // CENARIO A2: Grafos completos, variando número de vértices de 3 até limite
    printf("\nCENARIO A2: Grafos completos, variando número de vértices [DFS]\n");
    for(int i = 3; i < 16; i++) {

        printf("\nVértices = %2d ", i);

        Graph graph = Graph(i);
        int edges = (i)*(i-1)/2;
        graph.initializeRandomGraph(edges);

        auto start = high_resolution_clock::now();
        graph.enumerateCyclesDFS();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        auto seconds = duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto microseconds = duration_cast<std::chrono::microseconds>(duration);

        cout << "-> duração: "
            << seconds.count() << " segundos, "
            << microseconds.count() << " microssegundos." << endl;
    }

    int vertex = 10;
    int edges = (vertex)*(vertex-1)/2;

    // CENARIO B1: Grafos nulos até completo de 10 vértices, variando número de arestas
    printf("\nCENARIO B1: Grafos nulo até completo de 10 vértices, variando número de arestas [Permutação]\n");
    for(int i = 0; i < edges; i++) {

        printf("\nArestas = %2d ", i);

        Graph graph = Graph(vertex);
        graph.initializeRandomGraph(i);

        auto start = high_resolution_clock::now();
        graph.enumerateCyclesPermutation();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        auto seconds = duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto microseconds = duration_cast<std::chrono::microseconds>(duration);

        cout << "-> duração: "
            << seconds.count() << " segundos, "
            << microseconds.count() << " microssegundos." << endl;
    }

    // CENARIO B2: Grafos nulos até completo de 10 vértices, variando número de arestas
    printf("\nCENARIO B2: Grafos nulo até completo de 10 vértices, variando número de arestas [DFS]\n");
    for(int i = 0; i < edges; i++) {

        printf("\nArestas = %2d ", i);

        Graph graph = Graph(vertex);
        graph.initializeRandomGraph(i);

        auto start = high_resolution_clock::now();
        graph.enumerateCyclesDFS();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        auto seconds = duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto microseconds = duration_cast<std::chrono::microseconds>(duration);

        cout << "-> duração: "
            << seconds.count() << " segundos, "
            << microseconds.count() << " microssegundos." << endl;
    }

    return 0;
}
