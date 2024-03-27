#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int source;
    int destination;

    Edge(int source, int destination) {
        this->source = source;
        this->destination = destination;
    }
};

#endif