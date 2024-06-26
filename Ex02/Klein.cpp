#include "Klein.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Função auxiliar para calcular a distância de edição entre duas árvores,
int treeEditDistanceHeavy(const vector<Node *> &heavySubtrees1, const vector<Node *> &heavySubtrees2)
{
    int size1 = heavySubtrees1.size();
    int size2 = heavySubtrees2.size();

    // Criar e inicializar a tabela de programação dinâmica
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));

    // Preencher a primeira linha e coluna da tabela
    for (int i = 1; i <= size1; ++i)
    {
        dp[i][0] = dp[i - 1][0] + subtreeSize(heavySubtrees1[i - 1]);
    }
    for (int j = 1; j <= size2; ++j)
    {
        dp[0][j] = dp[0][j - 1] + subtreeSize(heavySubtrees2[j - 1]);
    }

    // Calcular a distância de edição
    for (int i = 1; i <= size1; ++i)
    {
        for (int j = 1; j <= size2; ++j)
        {
            int removeT1 = dp[i - 1][j] + subtreeSize(heavySubtrees1[i - 1]);
            int removeT2 = dp[i][j - 1] + subtreeSize(heavySubtrees2[j - 1]);
            int transform = dp[i - 1][j - 1] +
                            ((Node::getLabel(heavySubtrees1[i - 1]) == Node::getLabel(heavySubtrees2[j - 1])) ? 0 : 1);

            dp[i][j] = min(removeT1, min(removeT2, transform));
        }
    }

    return dp[size1][size2];
}

int treeEditDistance(Node *tree1, Node *tree2)
{
    // Obter as subárvores pesadas (apenas uma vez)
    vector<Node *> heavySubtrees1 = decomposeTree(tree1);
    vector<Node *> heavySubtrees2 = decomposeTree(tree2);

    return treeEditDistanceHeavy(heavySubtrees1, heavySubtrees2);
}

// Função auxiliar para calcular o tamanho da subárvore enraizada em um nó
int subtreeSize(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int size = 1;
    for (Node *child : root->children)
    {
        size += subtreeSize(child);
    }
    return size;
}

void decomposeTree(Node *root, vector<Node *> &heavySubtrees)
{
    if (root == nullptr)
    {
        return;
    }

    // Encontra TODOS os filhos com a maior subárvore
    int maxChildSize = 0;
    vector<Node *> heaviestChildren;
    for (Node *child : root->children)
    {
        int childSize = subtreeSize(child);
        if (childSize > maxChildSize)
        {
            // Novo tamanho máximo encontrado, limpa a lista de filhos mais pesados
            maxChildSize = childSize;
            heaviestChildren.clear();
            heaviestChildren.push_back(child);
        }
        else if (childSize == maxChildSize)
        {
            // Empate no tamanho máximo, adiciona o filho à lista de filhos mais pesados
            heaviestChildren.push_back(child);
        }
    }

    // Adiciona todos os filhos mais pesados na lista de subárvores pesadas
    for (Node *heavyChild : heaviestChildren)
    {
        heavySubtrees.push_back(heavyChild);
        decomposeTree(heavyChild, heavySubtrees);
    }
}

vector<Node *> decomposeTree(Node *root)
{
    vector<Node *> heavySubtrees;
    heavySubtrees.push_back(root);
    decomposeTree(root, heavySubtrees);
    return heavySubtrees;
}
