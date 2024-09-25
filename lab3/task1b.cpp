#include <iostream>

using namespace::std;

int ** create_matrix(int rows, int cols);
void print_matrix(int **matrix);
void print_result(int *result);
void get_user_input(int **matrix, int *vector);
int * matrix_vector_multiply(int **matrix, int *vector);

int vector_size, rows, cols;

int main () {
    
    // Keep asking for sizes as long as the vector and matrix cannot be multiplied
    do {
        cout << "Enter size of vector: ";
        cin >> vector_size;

        cout << "Enter the size of the matrix (m x n): ";
        cin >> rows >> cols;
    } while (vector_size != cols);

    // Create vector, result vector and matrix dynamically
    int *vector = new int[vector_size];
    int *result = new int[rows];
    int **matrix = create_matrix(rows, rows);

    // Get user inputs for matrix and vector
    get_user_input(matrix, vector);

    // Print the matrix
    print_matrix(matrix);

    // Calcualte result
    result = matrix_vector_multiply(matrix, vector);

    // Print result
    print_result(result);

    // Deacclocate all the vectors and matrices
    for (int i = 0; i < rows; i++) 
        delete[] matrix[i];
    delete[] matrix;
    delete[] result;
    delete[] vector;

    return 0;
}

int ** create_matrix(int rows, int cols) {
    int **matrix = new int*[rows];  

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    return matrix;
}

void print_matrix(int **matrix) {
     // Print matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void print_result(int *result) {
    cout << "Result: "<< "[ ";
    for (int i = 0; i < vector_size; i++) 
        cout << result[i] << " ";
    cout << "]" << endl;
}

void get_user_input(int **matrix, int *vector) {
    cout << "Enter the values for matrix: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Enter element " << i << " x " << j << ": ";
            cin >> matrix[i][j];
        }
    }

    cout << endl << "Enter values for vector: " << endl;
    for (int i = 0; i < vector_size; i++) {
        cout << " Enter vector element " << i << ": ";
        cin >> vector[i];
    }
}

int * matrix_vector_multiply(int **matrix, int *vector) {
    int *result = new int[rows];
    // Calculate the matrix-vector product
    for (int i = 0; i < vector_size; i++)
        for (int j = 0; j < cols; j++)
            result[j] += vector[i] * matrix[j][i];

    return result;
}