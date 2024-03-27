#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

#define Vertex int

using namespace std;

class Graph {
public:
    int numVertex;
    vector<vector<bool>> adjacencyMatrix;

    Graph(int numVertex) {
        this->numVertex = numVertex;
        adjacencyMatrix.resize(numVertex, vector<bool>(numVertex, 0));
    }

    void add(Vertex source, Vertex destination) {
        adjacencyMatrix[source][destination] = 1;
        adjacencyMatrix[destination][source] = 1;
    }

    void remove(Vertex source, Vertex destination) {
        adjacencyMatrix[source][destination] = 0;
        adjacencyMatrix[destination][source] = 0;
    }

    void reset() {
        for (int i = 0; i < numVertex; i++) {
            for (int j = 0; j < numVertex; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void print() {
        for (int i = 0; i < numVertex; i++) {
            // printf("%3d ", i + 1);
            for (int j = 0; j < numVertex; j++) {
                if (adjacencyMatrix[i][j])
                    printf("x ");
                else
                    printf("  ");
            }
            printf("\n");
        }
    }

    void initializeRandomGraph(int edgesCount) {

        reset();

        srand(1);

        int maxEdges = numVertex * (numVertex - 1) / 2;
        edgesCount = min(edgesCount, maxEdges);

        int addedEdges = 0;
        while (addedEdges < edgesCount) {
            Vertex source = rand() % numVertex;
            Vertex destination = rand() % numVertex;

            if (source != destination && adjacencyMatrix[source][destination] == 0) {
                add(source, destination);
                addedEdges++;
            }
        }
    }

    bool hasCycle(Vertex vertexArray[], int n) {
        bool hasCycle = true;

        for(int i = 0; i < n-1; i++) {
            hasCycle = hasCycle && (adjacencyMatrix[i][i+1] == 1);
        }
        hasCycle = hasCycle && (adjacencyMatrix[0][n-1] == 1);

        return hasCycle;
    }
};

#endif