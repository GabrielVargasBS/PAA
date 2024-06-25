#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    string label;
    vector<Node *> children;

    // Construtor que inicializa o nó com um rótulo e uma lista opcional de nós filhos
    Node(string label, vector<Node *> children = {});

    // Adiciona um nó filho a este nó
    void addKid(Node *child, bool before = false);

    // Adiciona múltiplos nós filhos a este nó
    void addChildren(vector<Node *> new_children);

    // Procura um nó com um determinado rótulo nesta subárvore
    Node *get(string search_label);

    // Método estático que retorna os filhos de um nó
    static vector<Node *> getChildren(Node *node);

    // Método estático que retorna o rótulo de um nó
    static string getLabel(Node *node);
};

#endif
