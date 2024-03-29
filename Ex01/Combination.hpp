#ifndef COMBINATION_H
#define COMBINATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define Vertex int

class Combination {
private:
    vector<Vertex> vertexArray;
    int combinationLength;
    vector<int> indices;
    vector<vector<Vertex>> combinations;

    bool hasNext() {
        int n = vertexArray.size();
        for (int i = combinationLength - 1; i >= 0; i--) {
            if (indices[i] != i + n - combinationLength) {
                return true;
            }
        }
        return false;
    }

    void generateNext() {
        int n = vertexArray.size();
        int i = combinationLength - 1;
        while (i >= 0 && indices[i] == i + n - combinationLength)
            i--;

        if (i >= 0) {
            indices[i]++;
            for (int j = i + 1; j < combinationLength; j++)
                indices[j] = indices[j - 1] + 1;
        }
    }

public:
    Combination(const vector<Vertex>& vertexArray, int combinationLength) {

        this->vertexArray = vertexArray;
        this->combinationLength = combinationLength;

        int n = vertexArray.size();
        for (int i = 0; i < combinationLength; i++)
            indices.push_back(i);
    }

    vector<vector<Vertex>> generateCombinations() {
        int n = vertexArray.size();
        if (combinationLength == n) {
            combinations.push_back(vertexArray);
        } else {
            while (hasNext()) {
                vector<Vertex> temp;
                for (int i = 0; i < combinationLength; i++) {
                    temp.push_back(vertexArray[indices[i]]);
                }
                combinations.push_back(temp);
                generateNext();
            }

            vector<Vertex> temp;
            for (int i = 0; i < combinationLength; i++) {
                temp.push_back(vertexArray[indices[i]]);
            }
            combinations.push_back(temp);
        }

        return combinations;
    }

};

#endif