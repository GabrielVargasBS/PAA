#include "Node.h"

// Construtor que inicializa o nó com um rótulo e uma lista opcional de nós filhos
Node::Node(string label, vector<Node *> children)
{
    this->label = label;
    this->children = children;
}

// Adiciona um nó filho a este nó
void Node::addKid(Node *child, bool before)
{
    if (before)
    {
        children.insert(children.begin(), child);
    }
    else
    {
        children.push_back(child);
    }
}

// Adiciona múltiplos nós filhos a este nó
void Node::addChildren(vector<Node *> new_children)
{
    children.insert(children.end(), new_children.begin(), new_children.end());
}

// Procura um nó com um determinado rótulo nesta subárvore
Node *Node::get(string search_label)
{
    if (label == search_label)
    {
        return this;
    }
    for (Node *child : children)
    {
        Node *result = child->get(search_label);
        if (result != nullptr)
        {
            return result;
        }
    }
    return nullptr;
}

// Método estático que retorna os filhos de um nó
vector<Node *> Node::getChildren(Node *node)
{
    return node->children;
}

// Método estático que retorna o rótulo de um nó
string Node::getLabel(Node *node)
{
    return node->label;
}
