#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stack>

#include "Permutation.hpp"
#include "Combination.hpp"

#define Vertex int

using namespace std;

class Graph
{
private:
    int numVertex;
    vector<vector<bool>> adjacencyMatrix;

    vector<vector<Vertex>> cyclesDFS;
    vector<vector<Vertex>> cyclesPermutation;

    void addNonDirectedEdge(Vertex source, Vertex destination)
    {
        adjacencyMatrix[source][destination] = 1;
        adjacencyMatrix[destination][source] = 1;
    }

    void addDirectedEdge(Vertex source, Vertex destination)
    {
        adjacencyMatrix[source][destination] = 1;
    }

    void reset()
    {
        for (int i = 0; i < numVertex; i++)
        {
            for (int j = 0; j < numVertex; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    bool hasCycle(vector<Vertex> vertexArray)
    {
        for (int i = 0; i < vertexArray.size() - 1; i++)
        {
            Vertex v = vertexArray[i];
            Vertex u = vertexArray[i + 1];
            if(adjacencyMatrix[v][u] == 0)
                return false;
        }

        // Last vertex must be adjacent to the first
        Vertex firstVertex = vertexArray[0];
        Vertex lastVertex = vertexArray[vertexArray.size() - 1];
        
        return (adjacencyMatrix[lastVertex][firstVertex] == 1);
    }

    bool areCyclesEqual(const vector<Vertex> &cycle1, const vector<Vertex> &cycle2)
    {
        if (cycle1.size() != cycle2.size())
            return false;

        int n = cycle1.size();
        for (int i = 0; i < n; i++)
        {
            bool equal = true;
            for (int j = 0; j < n; j++)
            {
                if (cycle1[j] != cycle2[(i + j) % n])
                {
                    equal = false;
                    break;
                }
            }
            if (equal)
                return true;
        }

        return false;
    }

    void enumerateCyclesDFSUtil(int v, vector<bool> &visited, stack<int> &path, int startVertex)
    {
        visited[v] = true;
        path.push(v);

        for (int i = 0; i < numVertex; ++i)
        {
            if (adjacencyMatrix[v][i])
            {
                if (!visited[i])
                {
                    enumerateCyclesDFSUtil(i, visited, path, startVertex);
                }
                else if (i == startVertex && path.size() >= 3)
                {
                    // Recupera o ciclo encontrado
                    vector<int> cycle;
                    stack<int> tempPath = path;

                    while (!tempPath.empty())
                    {
                        cycle.push_back(tempPath.top());
                        if (tempPath.top() == startVertex)
                        {
                            break;
                        }
                        tempPath.pop();
                    }

                    // Armazena o ciclo encontrado
                    cyclesDFS.push_back(cycle);
                }
            }
        }

        path.pop();
        visited[v] = false;
    }

public:
    Graph(int numVertex)
    {
        this->numVertex = numVertex;
        adjacencyMatrix.resize(numVertex, vector<bool>(numVertex, 0));
    }

    void print()
    {
        for (int i = 0; i < numVertex; i++)
        {
            for (int j = 0; j < numVertex; j++)
            {
                if (adjacencyMatrix[i][j])
                    printf("x ");
                else
                    printf("  ");
            }
            printf("\n");
        }
    }

    void initializeRandomNonDirectedGraph(int edgesCount)
    {

        reset();

        srand(time(nullptr));

        int maxEdges = numVertex * (numVertex - 1) / 2;
        edgesCount = min(edgesCount, maxEdges);

        int addedEdges = 0;
        while (addedEdges < edgesCount)
        {
            Vertex source = rand() % numVertex;
            Vertex destination = rand() % numVertex;

            if (source != destination && adjacencyMatrix[source][destination] == 0)
            {
                addNonDirectedEdge(source, destination);
                addedEdges++;
            }
        }
    }

    void initializeRandomDirectedGraph(int edgesCount)
    {

        reset();

        srand(time(nullptr));

        int maxEdges = numVertex * (numVertex - 1);
        edgesCount = min(edgesCount, maxEdges);

        int addedEdges = 0;
        while (addedEdges < edgesCount)
        {
            Vertex source = rand() % numVertex;
            Vertex destination = rand() % numVertex;

            if (source != destination && adjacencyMatrix[source][destination] == 0)
            {
                addDirectedEdge(source, destination);
                addedEdges++;
            }
        }
    }

    const vector<vector<Vertex>> &getCyclesDFS() const
    {
        return cyclesDFS;
    }

    const vector<vector<Vertex>> &getCyclesPermutation() const
    {
        return cyclesPermutation;
    }

    void enumerateCyclesPermutation()
    {
        // Inicialize o vetor de vértices
        vector<Vertex> vertexArray(numVertex);
        for (int i = 0; i < numVertex; ++i)
        {
            vertexArray[i] = i;
        }

        // Loop em todos os tamanhos de ciclo possíveis com k > 2
        for (int k = 3; k <= numVertex; k++)
        {
            // Obtenha todas as combinações de vértices possíveis sem repetição
            Combination comb(vertexArray, k);
            vector<vector<Vertex>> vertexCombination = comb.generateCombinations();

            // Para cada combinação de k vértices, obtenha todas as permutações possíveis
            for (vector<Vertex> combination : vertexCombination)
            {
                Permutation perm(combination);

                vector<Vertex> vertexPermutation = combination;

                do
                {
                    if (hasCycle(vertexPermutation))
                    {
                        // Armazena o ciclo encontrado
                        cyclesPermutation.push_back(vertexPermutation);
                    }

                    vertexPermutation = perm.nextPermutation();

                } while (!vertexPermutation.empty());
            }
        }
    }

    void enumerateCyclesDFS()
    {
        vector<bool> visited(numVertex, false);
        stack<int> path;

        for (int i = 0; i < numVertex; i++)
        {
            enumerateCyclesDFSUtil(i, visited, path, i);
        }
    }

    void printCycles(vector<vector<Vertex>> cycles)
    {
        printf("\nCiclos encontrados:\n");
        for (const auto &cycle : cycles)
        {
            for (const auto &vertex : cycle)
            {
                printf("%d ", vertex);
            }
            printf("\n");
        }
    }

    int findEqualCycles()
    {
        int equalCyclesCount = 0;
        for (const auto &cycleDFS : cyclesDFS)
        {
            for (const auto &cyclePerm : cyclesPermutation)
            {
                if (areCyclesEqual(cycleDFS, cyclePerm))
                {
                    equalCyclesCount++;
                    printf("\nCiclo igual encontrado: [");
                    for (const auto &vertex : cycleDFS)
                    {
                        printf("%d ", vertex);
                    }
                    printf("\b]\n");
                    break; // Para verificar o próximo ciclo DFS
                }
            }
        }

        return equalCyclesCount;
    }

};

#endif