#include <iostream>

using namespace::std;

int main() {
    
    int size;
    float sum, avg;
    // Input the size of dynamic array
    cout << "How many numbers do you want to enter? ";
    cin >> size;
    // Create a dynamic arrau of size >size<
    int *array_ptr = new int[size];
    // Iterate through the array and fill it with user input
    for (int i = 0; i < size; i++) {
        cout << "Enter number " << i + 1 << ": ";
        cin >> *(array_ptr + i);

        // Calculate the sum of inputs
        sum += *(array_ptr + i);
    }
    // Cacluate the average
    avg = sum/size;
    // Print everything out
    cout << "Array = [";  
    for (int i = 0; i < size; i++) 
        cout << *(array_ptr + i) << " ";
    cout << "]" << endl;

    cout << "Sum = " << sum << endl;
    cout << "Average = " << avg << endl;

    delete [] array_ptr;

}