#include "Klein.h"

// Função auxiliar para calcular a distância de edição entre duas árvores,
// dadas suas subárvores pesadas
int treeEditDistanceHeavy(const std::vector<Node *> &heavySubtrees1,
                          const std::vector<Node *> &heavySubtrees2)
{
    int size1 = heavySubtrees1.size();
    int size2 = heavySubtrees2.size();

    // 2. Criar e inicializar a tabela de programação dinâmica
    std::vector<std::vector<int>> dp(size1 + 1, std::vector<int>(size2 + 1, 0));

    // 3. Preencher a primeira linha e coluna da tabela
    for (int i = 1; i <= size1; ++i)
    {
        dp[i][0] = dp[i - 1][0] + subtreeSize(heavySubtrees1[i - 1]);
    }
    for (int j = 1; j <= size2; ++j)
    {
        dp[0][j] = dp[0][j - 1] + subtreeSize(heavySubtrees2[j - 1]);
    }

    // 4. Calcular a distância de edição
    for (int i = 1; i <= size1; ++i)
    {
        for (int j = 1; j <= size2; ++j)
        {
            int removeT1 = dp[i - 1][j] + subtreeSize(heavySubtrees1[i - 1]);
            int removeT2 = dp[i][j - 1] + subtreeSize(heavySubtrees2[j - 1]);
            int transform = dp[i - 1][j - 1] +
                            ((Node::getLabel(heavySubtrees1[i - 1]) == Node::getLabel(heavySubtrees2[j - 1])) ? 0 : 1);

            dp[i][j] = std::min(removeT1, std::min(removeT2, transform));
        }
    }

    return dp[size1][size2];
}

int treeEditDistance(Node *tree1, Node *tree2)
{

    // 1. Obter as subárvores pesadas (apenas uma vez)
    std::vector<Node *> heavySubtrees1 = decomposeTree(tree1);
    std::vector<Node *> heavySubtrees2 = decomposeTree(tree2);

    // 2. Chamar a função auxiliar para calcular a distância
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

void decomposeTree(Node *root, std::vector<Node *> &heavySubtrees)
{
    if (root == nullptr)
    {
        return;
    }

    // Encontra TODOS os filhos com a maior subárvore
    int maxChildSize = 0;
    std::vector<Node *> heaviestChildren;
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

    // Decompõe recursivamente TODOS os filhos mais pesados
    for (Node *heavyChild : heaviestChildren)
    {
        heavySubtrees.push_back(heavyChild);
        decomposeTree(heavyChild, heavySubtrees);
    }
}
std::vector<Node *> decomposeTree(Node *root)
{
    std::vector<Node *> heavySubtrees;
    heavySubtrees.push_back(root); // A raiz sempre é uma subárvore pesada
    decomposeTree(root, heavySubtrees);
    return heavySubtrees;
}