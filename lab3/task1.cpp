#include <iostream>

using namespace::std;

int main () {
    int vector_size = 3, rows = 3, cols = 3;
    int matrix[rows][cols], vector[3], result[3] = {0, 0, 0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    cout << "Result: ";
    for (int i = 0; i < vector_size; i++) {
        for (int j = 0; j < cols; j++) {
            result[j] += vector[i] * matrix[j][i];
        }
        cout << result[i] << " ";
    }
}

