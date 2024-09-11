#include <iostream>

using namespace::std;

// Swaps the contents using pointers
void pointer_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Swaps the contents using doble pointers
void double_pointer_swap(int **a, int **b) {
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main() { 
    int a=5, b=10; 
	int *pa=&a; // pa and pb are pointer variables of type int. 
	int *pb=&b;
	
	int **ppa=&pa; // ppa and ppb are called double pointers or pointers-to-pointers.
	int **ppb=&pb;

    // Testing and printing
    cout << "Swapping using pointers: " << endl;
    cout << "a = " << a << ", b = " << b << endl;
    pointer_swap(pa, pb);
    cout << "After swapping: a = " << a << ", b = " << b << endl;

    cout << "Swapping using double pointers: " << endl;
    cout << "a = " << a << ", b = " << b << endl;
    double_pointer_swap(ppa, ppb);
    cout << "After swapping: a = " << a << ", b = " << b << endl;
}