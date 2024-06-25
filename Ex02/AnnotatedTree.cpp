#include "AnnotatedTree.h"

AnnotatedTree::AnnotatedTree(Node *root, function<vector<Node *>(Node *)> get_children)
{
    // Stack for DFS traversal
    vector<pair<Node *, vector<int>>> stack;
    vector<tuple<Node *, int, vector<int>>> pstack;
    stack.push_back({root, {}});

    int j = 0;
    while (!stack.empty())
    {
        std::cout << "Iniciando iteracao do loop while em AnnotatedTree::AnnotatedTree" << std::endl;
        Node *n;
        vector<int> anc;
        tie(n, anc) = stack.back();
        stack.pop_back();

        std::cout << "Processando nó: " << Node::getLabel(n) << std::endl;

        // Imprima os filhos do nó atual
        auto children = get_children(n);
        std::cout << "Filhos do nó " << Node::getLabel(n) << ": ";
        for (auto child : children)
        {
            std::cout << Node::getLabel(child) << " ";
        }
        std::cout << std::endl;

        int nid = j;
        for (Node *c : get_children(n))
        {
            vector<int> a = anc;
            a.insert(a.begin(), nid);
            stack.push_back({c, a});
        }
        pstack.push_back({n, nid, anc});
        j++;
    }

    map<int, int> lmds_map;
    map<int, int> keyroots_map;
    int i = 0;
    while (!pstack.empty())
    {
        Node *n;
        int nid;
        vector<int> anc;
        tie(n, nid, anc) = pstack.back();
        pstack.pop_back();
        nodes.push_back(n);
        ids.push_back(nid);
        int lmd;
        if (get_children(n).empty())
        {
            lmd = i;
            for (int a : anc)
            {
                if (lmds_map.count(a))
                    break;
                lmds_map[a] = i;
            }
        }
        else
        {
            lmd = lmds_map[nid];
        }
        lmds.push_back(lmd);
        keyroots_map[lmd] = i;
        i++;
    }

    for (auto const &pair : keyroots_map)
    {
        keyroots.push_back(pair.second);
    }

    sort(keyroots.begin(), keyroots.end());
}

int AnnotatedTree::bool_dist(const std::string &foo, const std::string &bar)
{
    return foo == bar ? 0 : 1;
}

double AnnotatedTree::simple_distance(
    Node *foo,
    Node *bar,
    std::function<std::vector<Node *>(Node *)> get_children,
    std::function<std::string(Node *)> get_label,
    std::function<int(std::string, std::string)> label_dist)
{
    auto insert = [label_dist, get_label](Node *node_bar)
    { return label_dist("", get_label(node_bar)); };
    auto remove = [label_dist, get_label](Node *node_foo)
    { return label_dist(get_label(node_foo), ""); };
    auto update = [label_dist, get_label](Node *node_foo, Node *node_bar)
    {
        return label_dist(get_label(node_foo), get_label(node_bar));
    };
    return distance(foo, bar, get_children, insert, remove, update);
}

double AnnotatedTree::distance(Node *foo, Node *bar,
                               std::function<std::vector<Node *>(Node *)> get_children,
                               std::function<double(Node *)> insert_cost,
                               std::function<double(Node *)> remove_cost,
                               std::function<double(Node *, Node *)> update_cost)
{
    std::cout << "Primeira linha de distance:" << std::endl;
    try
    {
        AnnotatedTree foo_tree(foo, get_children);
        AnnotatedTree bar_tree(bar, get_children);

        std::cout << "Numero de nos na arvore foo: " << foo_tree.nodes.size() << std::endl;
        std::cout << "Numero de nos na arvore bar: " << bar_tree.nodes.size() << std::endl;

        std::vector<std::vector<double>> treedists(foo_tree.nodes.size(), std::vector<double>(bar_tree.nodes.size(), 0));

        auto treedist = [&](int i, int j)
        {
            std::vector<int> &fool = foo_tree.lmds;
            std::vector<int> &barl = bar_tree.lmds;
            std::vector<Node *> &foon = foo_tree.nodes;
            std::vector<Node *> &barn = bar_tree.nodes;

            int m = i - fool[i] + 2;
            int n = j - barl[j] + 2;
            std::vector<std::vector<double>> fd(m, std::vector<double>(n, 0));

            int ioff = fool[i] - 1;
            int joff = barl[j] - 1;

            for (int x = 1; x < m; ++x)
            {
                fd[x][0] = fd[x - 1][0] + remove_cost(foon[x + ioff]);
            }
            for (int y = 1; y < n; ++y)
            {
                fd[0][y] = fd[0][y - 1] + insert_cost(barn[y + joff]);
            }
            for (int x = 1; x < m; ++x)
            {
                for (int y = 1; y < n; ++y)
                {
                    if (fool[i] == fool[x + ioff] && barl[j] == barl[y + joff])
                    {
                        fd[x][y] = std::min({fd[x - 1][y] + remove_cost(foon[x + ioff]),
                                             fd[x][y - 1] + insert_cost(barn[y + joff]),
                                             fd[x - 1][y - 1] + update_cost(foon[x + ioff], barn[y + joff])});
                        treedists[x + ioff][y + joff] = fd[x][y];

                        std::cout << "Atualizando treedists[" << x + ioff << "][" << y + joff << "] = " << fd[x][y] << std::endl;
                    }
                    else
                    {
                        int pi = fool[x + ioff] - 1 - ioff;
                        int qi = barl[y + joff] - 1 - joff;
                        fd[x][y] = std::min({fd[x - 1][y] + remove_cost(foon[x + ioff]),
                                             fd[x][y - 1] + insert_cost(barn[y + joff]),
                                             fd[pi][qi] + treedists[x + ioff][y + joff]});

                        std::cout << "Calculando fd[" << x << "][" << y << "] = " << fd[x][y] << std::endl;
                    }
                }
            }
        };

        for (int i : foo_tree.keyroots)
        {
            for (int j : bar_tree.keyroots)
            {
                std::cout << "Calculando treedist para i = " << i << ", j = " << j << std::endl;
                treedist(i, j);
            }
        }

        std::cout << "Ultima linha de distance:" << std::endl;
        std::cout << "Valor final de treedists: " << treedists.back().back() << std::endl;
        return treedists.back().back();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exceção capturada: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Exceção desconhecida capturada" << std::endl;
    }

    return 0; // Retorne algum valor padrão ou lance uma exceção aqui
}
