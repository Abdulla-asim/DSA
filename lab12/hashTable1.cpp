#include <iostream>
#include <string>

using namespace std;

class HashTable {
public:
    int *table;
    int size;

    HashTable(int size) {
        this->size = size;
        table = new int[size];
    }

    void insert(int key, int value) {
        int index = key;
        if (key >= size || key < 0) {
            cout << "[INFO] Index out of bounds." << endl;
            return;
        }
        table[index] = value;
        cout << "[INFO] Inserted.." << endl;
    }

    int get(int key) {
        if (key >= size || key < 0) {
            cout << "[INFO] Index out of bounds." << endl;
            return -1;
        }
        return table[key];
    }

    void remove(int key) {
        if (key >= size || key < 0) {
            cout << "[INFO] Index out of bounds." << endl;
            return;
        }
        table[key] = -1;
        cout << "[INFO] Removed.." << endl;
    }

    bool search(int key, int value) {
        if (key >= size || key < 0) {
            cout << "[INFO] Index out of bounds." << endl;
            return false;
        }
        return table[key] == value;
    }

    void print() {
        cout << "{ " << endl;
        for (int i = 0; i < size; i++) {
            if (table[i] != -1)
                cout << i << ": " << table[i] << ", ";
        }
        cout << endl << "}" << endl;
    }
};

int main() {
    HashTable table(10);
    table.insert(0, 1);
    table.insert(1, 2);
    table.insert(2, 3);
    table.insert(3, 4);
    table.insert(4, 5);
    table.insert(5, 6);
    table.insert(6, 7);
    table.insert(7, 8);
    table.insert(8, 9);
    table.insert(9, 10);
    table.print();

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Get" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Print" << endl;
        cout << "5. Search" << endl;
        cout << "6. Exit" << endl;
        cout << "____________________" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Enter key: ";
                int key;
                cin >> key;
                cout << "Enter value: ";
                int value;
                cin >> value;
                table.insert(key, value);
                break;
            }
            case 2: {
                cout << "Enter key: ";
                int key;
                cin >> key;
                cout << "Value: " << table.get(key) << endl;
                break;
            }
            case 3: {
                cout << "Enter key: ";
                int key;
                cin >> key;
                table.remove(key);
                break;
            }
            case 4: {
                cout << "____________________" << endl;
                table.print();
                break;
            }
            case 5: {
                cout << "Enter key: ";
                int key;
                cin >> key;
                cout << "Enter value: ";
                int value;
                cin >> value;
                cout << "Found: " << table.search(key, value) << endl;
                break;
            }
            case 6: {
                cout << "{INFO] Exiting.." << endl;
                return 0;
            }
            default: {
                cout << "[INFO] Invalid choice." << endl;
                break;
            }
        }
    }
    return 0;
}