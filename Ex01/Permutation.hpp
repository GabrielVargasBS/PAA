#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <iostream>
#include <vector>

using namespace std;
#define Vertex int

class Permutation {
private:
    vector<Vertex> vertexArray;

    void swap(Vertex& a, Vertex& b) {
        Vertex temp = a;
        a = b;
        b = temp;
    }

    void reverse(int start, int end) {
        for (int i = start; i < end; i++, end--) {
            swap(vertexArray[i], vertexArray[end]);
        }
    }

public:
    Permutation(const vector<Vertex>& array) {
        vertexArray = array;
    }

    vector<Vertex> nextPermutation() {

        int size = vertexArray.size();
        int i = size - 2;

        while (i >= 0 && vertexArray[i] >= vertexArray[i + 1]) {
            i--;
        }

        if (i < 0) {
            vector<int> vetEmpty;
            return vetEmpty;
        }

        int j = size - 1;

        while (vertexArray[j] <= vertexArray[i]) {
            j--;
        }

        swap(vertexArray[i], vertexArray[j]);
        reverse(i + 1, size - 1);

        return vertexArray;
    }

};

#endif
