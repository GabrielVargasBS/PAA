#include "Graph.hpp"

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

int main()
{
    Graph g = Graph(8);
    g.initializeRandomGraph(4);
    g.print();

    int count1 = 0;
    g.enumerateCyclesPermutation(&count1);

    int count2 = 0;
    g.enumerateCyclesDFS(&count2);

    // Obtém os ciclos encontrados
    const vector<vector<Vertex>> &cyclesDFS = g.getCyclesDFS();
    const vector<vector<Vertex>> &cyclesPermutation = g.getCyclesPermutation();

    printf("\nCiclos encontrados por permutacao:\n");
    for (const auto &cycle : cyclesPermutation)
    {
        for (const auto &vertex : cycle)
        {
            printf("%d ", vertex);
        }
        printf("\n");
    }

    printf("\nCiclos encontrados por DFS:\n");
    for (const auto &cycle : cyclesDFS)
    {
        for (const auto &vertex : cycle)
        {
            printf("%d ", vertex);
        }
        printf("\n");
    }

    printf("\nCount Permutation = %d", count1);
    printf("\nCount DFS = %d", count2);
    printf("\n");

    // Verifica e conta os ciclos iguais
    int equalCyclesCount = 0;
    for (const auto &cycleDFS : cyclesDFS)
    {
        for (const auto &cyclePerm : cyclesPermutation)
        {
            if (areCyclesEqual(cycleDFS, cyclePerm))
            {
                equalCyclesCount++;
                printf("\nCiclo igual encontrado:\n");
                for (const auto &vertex : cycleDFS)
                {
                    printf("%d ", vertex);
                }
                printf("\n");
                break; // Para verificar o próximo ciclo DFS
            }
        }
    }

    printf("\nCiclos iguais encontrados: %d\n", equalCyclesCount);

    return 0;
}
