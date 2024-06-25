#include <iostream>
#include "AnnotatedTree.h"

int main()
{
    // Construindo a primeira árvore
    Node *root1 = new Node("A");
    Node *child1 = new Node("B");
    Node *child2 = new Node("C");
    root1->addChildren({child1, child2});
    child1->addChildren({new Node("D"), new Node("E")});

    // Construindo a segunda árvore
    Node *root2 = new Node("A");
    Node *child3 = new Node("B");
    Node *child4 = new Node("C");
    root2->addChildren({child3, child4});
    child3->addChildren({new Node("D"), new Node("F")});

    // Calculando a distância entre as duas árvores
    double dist = AnnotatedTree::simple_distance(root1, root2);

    std::cout << "Distancia entre as duas arvores: " << dist << std::endl;

    // Limpando a memória
    delete root1; // Esta linha apenas deleta o nó raiz. Adicione a lógica necessária para deletar todos os nós.
    delete root2; // Esta linha apenas deleta o nó raiz. Adicione a lógica necessária para deletar todos os nós.

    return 0;
}
