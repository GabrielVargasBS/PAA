#include <iostream>
#include "AnnotatedTree.h"
#include "Klein.h"
#include <cstdlib>
#include <ctime>

Node *generateRandomTree(int maxDepth, int maxValue, int &nodeCount)
{
    if (maxDepth == 0)
    {
        return nullptr;
    }

    // Gere um valor aleatório entre 1 e maxValue
    int value = rand() % maxValue + 1;
    Node *root = new Node(std::to_string(value));
    nodeCount++;

    // Gere de 0 a 2 filhos recursivamente
    int numChildren = rand() % 3; // 0, 1 ou 2 filhos
    for (int i = 0; i < numChildren; ++i)
    {
        root->addKid(generateRandomTree(maxDepth - 1, maxValue, nodeCount), false);
    }

    return root;
}

void printTree(Node *root, const std::string &prefix = "", bool isLast = true)
{
    if (root == nullptr)
    {
        return;
    }

    std::cout << prefix;
    if (isLast)
    {
        std::cout << "\\--";
    }
    else
    {
        std::cout << "|-- ";
    }
    std::cout << root->label << std::endl;

    for (size_t i = 0; i < root->children.size(); ++i)
    {
        bool lastChild = (i == root->children.size() - 1);
        printTree(root->children[i], prefix + (isLast ? "    " : "|   "), lastChild);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int maxDepth = 7;  // Profundidade máxima da árvore
    int maxValue = 30; // Valor máximo dos nós
    int nodeCount1 = 0, nodeCount2 = 0;

    // Gere as árvores aleatoriamente
    Node *root1 = generateRandomTree(maxDepth, maxValue, nodeCount1);
    Node *root2 = generateRandomTree(maxDepth, maxValue, nodeCount2);

    // Imprime as árvores geradas
    std::cout << "Arvore 1:" << std::endl;
    printTree(root1);
    std::cout << std::endl;

    std::cout << "Arvore 2:" << std::endl;
    printTree(root2);
    std::cout << std::endl;

    double dist = AnnotatedTree::simple_distance(root1, root2);
    std::cout << "Distancia entre as duas arvores por Zhang and Sasha: " << dist << std::endl;

    int distance = treeEditDistance(root1, root2);
    std::cout << "Distancia entre as duas arvores por Klein: " << distance << std::endl;

    delete root1;
    delete root2;

    return 0;
}
