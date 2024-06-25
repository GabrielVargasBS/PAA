#ifndef ANNOTATEDTREE_H
#define ANNOTATEDTREE_H

#include <vector>
#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include "Node.h"
#include <iostream>

using namespace std;

class AnnotatedTree
{
public:
    vector<Node *> nodes;
    vector<int> ids;
    vector<int> lmds;
    vector<int> keyroots;

    AnnotatedTree(Node *root, function<vector<Node *>(Node *)> get_children);

    static int bool_dist(const std::string &foo, const std::string &bar);

    static double simple_distance(
        Node *foo,
        Node *bar,
        std::function<std::vector<Node *>(Node *)> get_children = Node::getChildren,
        std::function<std::string(Node *)> get_label = Node::getLabel,
        std::function<int(std::string, std::string)> label_dist = bool_dist);

    static double distance(Node *foo, Node *bar,
                           std::function<std::vector<Node *>(Node *)> get_children,
                           std::function<double(Node *)> insert_cost,
                           std::function<double(Node *)> remove_cost,
                           std::function<double(Node *, Node *)> update_cost);
};

#endif
