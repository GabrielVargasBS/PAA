#ifndef COMBINATION_H
#define COMBINATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Combination {
private:
    vector<int> vertexArray;
    int r;
    vector<int> indices;
    vector<vector<int>> combinations;

    bool hasNext() {
        int n = vertexArray.size();
        for (int i = r - 1; i >= 0; i--) {
            if (indices[i] != i + n - r) {
                return true;
            }
        }
        return false;
    }

    void generateNext() {
        int n = vertexArray.size();
        int i = r - 1;
        while (i >= 0 && indices[i] == i + n - r)
            i--;

        if (i >= 0) {
            indices[i]++;
            for (int j = i + 1; j < r; j++)
                indices[j] = indices[j - 1] + 1;
        }
    }

public:
    Combination(const vector<int>& _vertexArray, int _r) : vertexArray(_vertexArray), r(_r) {
        int n = vertexArray.size();
        for (int i = 0; i < r; i++)
            indices.push_back(i);
    }

    vector<vector<int>> generateCombinations() {
        int n = vertexArray.size();
        if (r == n) {
            combinations.push_back(vertexArray);
        } else {
            while (hasNext()) {
                std::vector<int> temp;
                for (int i = 0; i < r; i++) {
                    temp.push_back(vertexArray[indices[i]]);
                }
                combinations.push_back(temp);
                generateNext();
            }

            std::vector<int> temp;
            for (int i = 0; i < r; i++) {
                temp.push_back(vertexArray[indices[i]]);
            }
            combinations.push_back(temp);
        }

        return combinations;
    }

};

#endif