#include <iostream>

using namespace std;

struct Pair
{
    int key;
    int value;
};

// DH: Double Hashing
class HashTable_DH {
public:
    Pair *table;
    int size;

    HashTable_DH(int size) 
    {
        this->size = size;
        table = new Pair[size];

        // Initialize the table with -1
        for (int i = 0; i < size; i++)
            table[i].value = -1;
    }

    void insert(int key, int value) 
    {
        int index = hash1(key);  // Get the primary hash index
        int step = hash2(key);  // Get the step size using the secondary hash

        for (int i = 0; i < size; i++) 
        {
            if (table[index].value == -1) 
            { // Found an empty slot
                table[index].value = value; // Insert the value
                cout << "[INFO] Inserted key: " << key << " value: " << value << " at index: " << index << endl;
                return;
            }
            index = (index + step) % size; // Move to the next index using double hashing
        }

        cout << "[ERROR] Hash table is full, could not insert key: " << key << endl;
    }

    int get(int key) 
    {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) 
        {
            if (table[index].value == -1) {
                return -1; // Key not found
            }
            index = (index + step) % size;
        }

        return table[index].value;
    }

    void remove(int key) 
    {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) 
        {
            if (table[index].value == -1) 
            {
                cout << "[INFO] Key not found for deletion: " << key << endl;
                return; // Key not found
            }
            table[index].value = -1;
            cout << "[INFO] Removed key: " << key << " from index: " << index << endl;
            return;
            index = (index + step) % size;
        }
    }

    bool search(int key) 
    {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) 
        {
            if (table[index].value == -1)
                return false; // not found
            if (table[index].key == key)
                return true;
            index = (index + step) % size;
        }
        return false;
    }

    void print() 
    {
        cout << "{ " << endl;
        for (int i = 0; i < size; i++) 
            if (table[i].value != -1)
                cout << i << ": " << table[i].value << ", ";

        cout << endl << "}" << endl;
    }

    // Primary Hash Function
    int hash1(int key) 
    {
        return key % size;
    }

    // Secondary Hash Function
    int hash2(int key) 
    {
        return 1 + (key % (size - 1)); // Ensure step size is non-zero
    }
};

int main() {
    HashTable_DH table(10);

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

        switch (choice) {
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
