#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

void mergeSort(int a[], int first, int last);
void merge(int[], int, int, int);

int main () {
    int s = 100;
    // initialize random number generator
    mt19937 rng(42);        // with seed: 42
    // for Uniform distribution 
    uniform_int_distribution<int> rand(1, 100);

    //// UNCOMMENT WHAT YOU DESIRE
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
        mergeSort(array, 0, SIZE);    

        ////// END TIMING
        auto end = chrono::high_resolution_clock::now();

        ///// TOTAL TIME
        chrono::duration<double> duration = end - start;

        cout << "Merge Sorted array: " << endl;
        cout << "Array Size: " << SIZE << endl;
        cout << "Time Taken: " << duration.count() * 1000 << " ms." << endl;
        cout << "----------------" << endl;
    }
    return 0;
}

// Merge sort
void mergeSort(int a[], int first_idx, int last_idx) {
    if (first_idx < last_idx) {
        int midpoint = (first_idx + last_idx) / 2;
        mergeSort(a, first_idx, midpoint);
        mergeSort(a, midpoint + 1, last_idx);
        merge(a, first_idx, midpoint + 1, last_idx);
    }
}

void merge(int arr[], int first, int mid, int last) {
    int a = first, b = mid, c = first;
    int B[1000000];

	while (a <= mid && b<=last) {
		if (arr[a] < arr[b] )
		    B[c++] = arr[a++];
		else
		    B[c++] = arr[b++];
    }

	while (a < mid)
		B[c++] = arr[a++];

	while (b < last)
		B[c++] = arr[b++];

	for (a = first; a <= last; a++)
		arr[a]=B[a];
}

// Print array function
void printArray(int a[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "]" << endl;
}