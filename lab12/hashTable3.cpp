#include <iostream>

using namespace std;

struct Pair
{
    int key;
    int value;
};

class HashTable_QP {
public:
    Pair *table;
    int size;

    HashTable_QP(int size) 
    {
        this->size = size;
        table = new Pair[size];

        // Initialize the table with -1
        for (int i = 0; i < size; i++) {
            table[i].value = -1;
        }
    }

    void insert(int key, int value) 
    {
        int index = hash(key);  // Get the index ( 0 to size - 1)
        for (int i = 1; table[index].value != -1; i++, index = (index + i*i) % size);  // Quadratic Probing
        table[index].value = value; // Insert the value
        cout << "[INFO] Inserted.." << endl;
    }

    int get(int key) 
    {
        int index = hash(key);
        return table[index].value;
    }

    void remove(int key) 
    {
        int index = hash(key);
        table[index].value = -1;
        cout << "[INFO] Removed.." << endl;
    }

    bool search(int key) 
    {
        int index = hash(key);
        int start_index = index;
        int i = 1;
        // Quadratic Probing
        while (table[index].value != -1) 
        {
            if (table[index].key == key)
                return true;
            index = (index * i*i) % size;
            i++;
            if (index == start_index)
                break;
        }
        return false;
    }

    void print() {
        cout << "{ " << endl;
        for (int i = 0; i < size; i++) {
            if (table[i].value != -1)
                cout << i << ": " << table[i].value << ", ";
        }
        cout << endl << "}" << endl;
    }

    // Hash Function
    int hash(int key) {
        return key % size;
    }
};

int main () {
    HashTable_QP table(10);

    while (true) {
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
                cout << "Found: " << table.search(key) << endl;
                break;
            }
            case 6: {
                cout << "[INFO] Exiting.." << endl;
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