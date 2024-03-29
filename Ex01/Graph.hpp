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
    void add(Vertex source, Vertex destination)
    {
        adjacencyMatrix[source][destination] = 1;
        adjacencyMatrix[destination][source] = 1;
    }

    void remove(Vertex source, Vertex destination)
    {
        adjacencyMatrix[source][destination] = 0;
        adjacencyMatrix[destination][source] = 0;
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
        bool hasCycle = true;

        for (int i = 0; i < vertexArray.size() - 1; i++)
        {
            Vertex v = vertexArray[i];
            Vertex u = vertexArray[i + 1];
            hasCycle = hasCycle && (adjacencyMatrix[v][u] == 1);
        }

        // Last vertex must be adjacent to the first
        Vertex firstVertex = vertexArray[0];
        Vertex lastVertex = vertexArray[vertexArray.size() - 1];
        hasCycle = hasCycle && (adjacencyMatrix[firstVertex][lastVertex] == 1);

        return hasCycle;
    }

public:
    int numVertex;
    vector<vector<bool>> adjacencyMatrix;

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

    void initializeRandomGraph(int edgesCount)
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
                add(source, destination);
                addedEdges++;
            }
        }
    }

    void enumerateCyclesPermutation(int *count)
    {

        // Inicialize the vertex
        vector<Vertex> vertexArray(numVertex);
        for (int i = 0; i < numVertex; ++i)
        {
            vertexArray[i] = i;
        }

        // Loop in all possible cycle sizes with k > 2
        for (int k = 3; k <= numVertex; k++)
        {

            printf("\nCycles with k = %d\n", k);

            // Get all possible vertex combinations without repetition
            Combination comb(vertexArray, k);
            vector<vector<Vertex>> vertexCombination = comb.generateCombinations();

            // For each combination of k vertices, get all possible permutations
            for (vector<Vertex> combination : vertexCombination)
            {

                Permutation perm(combination);

                vector<Vertex> vertexPermutation = combination;

                do
                {
                    if (hasCycle(vertexPermutation))
                    {
                        printf("Cycle: ");
                        for (int i = 0; i < vertexPermutation.size(); i++)
                        {
                            printf("%d ", vertexPermutation[i]);
                        }
                        printf("%d\n", vertexPermutation[0]);
                        *count = *count + 1;
                    }

                    vertexPermutation = perm.nextPermutation();

                } while (!vertexPermutation.empty());
            }
        }
    }

    void enumerateCyclesDFSUtil(int v, vector<bool> &visited, stack<int> &path, int startVertex, int *count)
    {
        visited[v] = true;
        path.push(v);

        for (int i = 0; i < numVertex; ++i)
        {
            if (adjacencyMatrix[v][i])
            {
                if (!visited[i])
                {
                    enumerateCyclesDFSUtil(i, visited, path, startVertex, count);
                }
                else if (i == startVertex && path.size() >= 3)
                {
                    stack<int> tempPath = path;
                    tempPath.pop(); // Remove o vértice repetido no início do ciclo

                    bool cycleFound = false;
                    vector<Vertex> cycle;

                    while (!tempPath.empty())
                    {
                        cycle.push_back(tempPath.top());
                        if (tempPath.top() == startVertex)
                        {
                            cycleFound = true;
                        }
                        tempPath.pop();
                    }

                    if (cycleFound)
                    {
                        printf("Cycle: ");
                        for (int i = cycle.size() - 1; i >= 0; i--)
                        {
                            printf("%d ", cycle[i]);
                        }
                        printf("%d\n", startVertex);
                        *count = *count + 1;
                    }
                }
            }
        }

        path.pop();
        visited[v] = false;
    }

    void
    enumerateCyclesDFS(int *count)
    {
        vector<bool> visited(numVertex, false);
        stack<int> path;

        for (int i = 0; i < numVertex; ++i)
        {
            enumerateCyclesDFSUtil(i, visited, path, i, count);
        }
    }
};

#endif