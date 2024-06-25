#include <vector>
#include <string>

using namespace std;

class Node {
public:
    string label;
    vector<Node*> children;

    // Construtor que inicializa o nó com um rótulo e uma lista opcional de nós filhos
    Node(string label, vector<Node*> children = {}) {
        this->label = label;
        this->children = children;
    } 

    // Adiciona um nó filho a este nó
    // Se 'before' for verdadeiro, o filho é inserido no início da lista de filhos
    // Caso contrário, é adicionado ao final
    void addKid(Node* child, bool before = false) {
        if (before) {
            children.insert(children.begin(), child);
        } else {
            children.push_back(child);
        }
    }

    // Procura um nó com um determinado rótulo nesta subárvore
    // Retorna o nó encontrado ou nullptr se nenhum nó com esse rótulo for encontrado
    Node* get(string search_label) {
        if (label == search_label) {
            return this;
        }
        for (Node* child : children) {
            Node* result = child->get(search_label);
            if (result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }

    // Método estático que retorna os filhos de um nó
    static vector<Node*> getChildren(Node* node) {
        return node->children;
    }

    // Método estático que retorna o rótulo de um nó
    static string getLabel(Node* node) {
        return node->label;
    }
};