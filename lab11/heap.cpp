#include <iostream>
#include <vector>
#include <climits>
#include <math.h>

using namespace std;

class MinHeap {
    vector<int> heap;

    int left_child(int i) {
        return 2 * i;
    }

    int right_child(int i) {
        return 2 * i + 1;
    }

    int parent(int i) {
        return i / 2;
    }

    void insert(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;
        while (i > 1 && heap[parent(i)] > heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void build_heap(int i) {
        int l = left_child(i);
        int r = right_child(i);
        int smallest = i;

        if (l < heap.size()) {
            if (heap[l] < heap[i]) 
                smallest = l;
            if (heap[r] < heap[smallest]) 
                smallest = r;
        }
        
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            build_heap(smallest);
        }
    }

    void delete_min() {
        if (heap.size() == 0) {
            return;
        }
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        build_heap(0);
    }

    public:
    MinHeap() {
        heap.push_back(INT_MIN);
    }

    int top() {
        if (heap.size() == 0) {
            return INT_MAX;
        }
        return heap[0];
    }

    void pop() {
        delete_min();
    }

    void push(int x) {
        insert(x);
    }

    bool is_empty() {
        return heap.size() <= 1;
    }

    int size() {
        return heap.size() - 1;
    }

    int height() {
        return log2(heap.size()-1);
    }

    void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }    
};

int main() {
    MinHeap heap;
    bool exit = true;
    
    while (exit) {
        cout << "Menu: " << endl;
        cout << "1. Insert element" << endl;
        cout << "2. Delete min element" << endl;
        cout << "3. Get top element" << endl;
        cout << "4. Get heap size" << endl;
        cout << "5. Get heap height" << endl;
        cout << "6. Print heap" << endl;
        cout << "7. Exit" << endl << "___________________" << endl;
        cout << "Enter your choice: ";
        int choice;

        do {
            cin >> choice;
            cin.ignore();
            if (choice < 1 || choice > 7) {
                cout << "Invalid choice. TRY AGAIN!" << endl;
            }
        } while (choice < 1 || choice > 7);

        switch(choice) {
            case 1: {
                cout << "Enter element to insert: ";
                int x;
                cin >> x;
                heap.push(x);
                break;
            }
            case 2: {
                cout << ">> Deleting min element: " << heap.top() << endl;
                heap.pop();
                break;
            }
            case 3: {
                cout << ">> Top element: " << heap.top() << endl;
                break;
            }
            case 4: {
                cout << ">> Heap size: " << heap.size() << endl;
                break;
            }
            case 5: {
                cout << ">> Heap height: " << heap.height() << endl;
                break;
            }
            case 6: {
                cout << ">> Heap: ";
                heap.print();
                break;
            }
            case 7: {
                exit = false;
                break;
            }
            default: {
                cout << "Invalid choice. TRY AGAIN!" << endl;
            }
        }
    }
}