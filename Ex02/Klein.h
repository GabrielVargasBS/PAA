
#ifndef KLEIN_H
#define KLEIN_H

#include "Node.h"
#include <vector>
#include <iostream>

// Função para calcular a distância de edição entre duas árvores
int treeEditDistance(Node *tree1, Node *tree2);

// Função auxiliar para calcular o tamanho da subárvore enraizada em um nó
int subtreeSize(Node *root);

// Função para decompor a árvore em subárvores pesadas
std::vector<Node *> decomposeTree(Node *root);

#endif