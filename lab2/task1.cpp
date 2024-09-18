#include<iostream>

using namespace::std;

int main() {

    int size;
    // Enter size of the array
    cout << "Enter the size of dynamic array: ";
    cin >>  size;

    int *d_array = new int[size];
    // Iterate, fill and print the values from 1 to size
    for (int i = 0; i < size; i++) {
        *(d_array + i) = i + 1;
        cout << "array[" << i << "] = " << i+1 << endl;
    }
    // Delete the dynamic array
    delete [] d_array;

    return 0;
}
