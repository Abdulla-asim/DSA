#include <iostream>
#include <random>
#include<chrono>
#include <algorithm>


using namespace std;

void selectionSort(int a[], int n);

int main () {
    int s = 100;
    // initialize random number generator
    mt19937 rng(42);        // with seed: 42
    // for Uniform distribution 
    uniform_int_distribution<int> rand(1, 100);

    //cout << "FOR ASCENDING ORDERED ARRAY: " << endl;
    cout << "FOR DESCENDING ORDERED ARRAY: " << endl;

    for (int SIZE = s; SIZE <= 1000000; SIZE *= 10){

        int array[SIZE];

        // Generating random numbers
        for (int i = 0; i < SIZE; i++) {
            array[i] = rand(rng);
        }

        //// UNCOMMENT TO Sort the array in ASCENDING order.
        //std::sort(array, array + SIZE);
        //// UNCOMMENT TO Sort the array in DESCENDING order.
        std::sort(array, array + SIZE, greater<int>());

        ////// START TIMING
        auto start = chrono::high_resolution_clock::now();

        // Sort array
        selectionSort(array, SIZE);    

        ////// END TIMING
        auto end = chrono::high_resolution_clock::now();

        ///// TOTAL TIME
        chrono::duration<double> duration = end - start;

        cout << "Selection Sorted array: " << endl;
        cout << "Array Size: " << SIZE << endl;
        cout << "Time Taken: " << duration.count() * 1000 << " ms." << endl;
        cout << "----------------" << endl;
    }
    return 0;
}

// Selection sort
void selectionSort(int a[], int n) {
    for (int i=n-1; i>0; i--) {         // Start from last element and decrement
        int max_index = i;
        for (int j=0; j<i; j++) {       // Go from start uptil the i th element
            if (a[j] > a[max_index])    // if previous element is greater than next element
                max_index = j;          // store its index
        }
        swap(a[i], a[max_index]); //swap
    }
}

// Print array function
void printArray(int a[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "]" << endl;
}