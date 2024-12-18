#include <iostream>
#include <chrono>

using namespace std;

struct Pair {
    int key;
    int value;
};

class HashTable_DA {
public:
    Pair *table;
    int size;

    HashTable_DA(int size) 
    {
        this->size = size;
        table = new Pair[size];
    }

    void insert(int key, int value) 
    {
        int index = key;
        if (key >= size || key < 0) 
        {
            cout << "[INFO] Index out of bounds." << endl;
            return;
        }
        table[index].value = value;
        cout << "[INFO] Inserted.." << endl;
    }

    int get(int key) 
    {
        if (key >= size || key < 0) 
        {
            cout << "[INFO] Index out of bounds." << endl;
            return -1;
        }
        return table[key].value;
    }

    void remove(int key) 
    {
        if (key >= size || key < 0) 
        {
            cout << "[INFO] Index out of bounds." << endl;
            return;
        }
        table[key].key = -1;
        cout << "[INFO] Removed.." << endl;
    }

    bool search(int key) 
    {
        if (key >= size || key < 0) 
        {
            cout << "[INFO] Index out of bounds." << endl;
            return false;
        }
        if (table[key].value == -1)
            return false;
        return table[key].value;
    }

    void print() {
        cout << "{ " << endl;
        for (int i = 0; i < size; i++) 
        {
            if (table[i].value != -1)
                cout << i << ": " << table[i].value << ", ";
        }
        cout << endl << "}" << endl;
    }
};


class HashTable_LP {
public:
    Pair *table;
    int size;

    HashTable_LP(int size) 
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
        for (; table[index].value != -1; index = (++index) % size);  // Find the next empty slot
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
        while (table[index].value != -1) 
        {
            if (table[index].key == key)
                return true;
            index = (++index) % size;
            if (index == start_index) // in case key is not found and the index reaches the start index circularly
                return false;
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

    // Hash Function
    int hash(int key) {
        return key % size;
    }
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

/*
int main() {
    // Initialize the hash tables
    HashTable_DA direct_addr = HashTable_DA(10);
    HashTable_LP linear_probing = HashTable_LP(10);
    HashTable_QP quadratic_probing = HashTable_QP(10);
    HashTable_DH double_hashing = HashTable_DH(10);

    // INsert into all the hash tables
    direct_addr.insert(1, 10);
    direct_addr.insert(2, 20);
    direct_addr.insert(2, 20);

    linear_probing.insert(1, 10);
    linear_probing.insert(2, 20);
    linear_probing.insert(2, 20);

    quadratic_probing.insert(1, 10);
    quadratic_probing.insert(2, 20);
    quadratic_probing.insert(2, 20);

    double_hashing.insert(1, 10);
    double_hashing.insert(2, 20);
    double_hashing.insert(2, 20);
    cout << endl;


    //Compare the time taken by Direct Addressing
    auto start = chrono::high_resolution_clock::now();
    direct_addr.search(4);
    auto end = chrono::high_resolution_clock::now();
    // Calculate the time taken
    chrono::duration<double, milli> duration = end - start;
    cout << "Search operation time for Direct Addressing: \t" << duration.count() << " milli seconds." << endl;

    // Compare the time taken by Linear Probing 
    start = chrono::high_resolution_clock::now();
    linear_probing.search(4);
    end = chrono::high_resolution_clock::now();
    // Calculate the time taken
    duration = end - start;
    cout << "Search operation time for Linear Probing: \t" << duration.count() << " milli seconds." << endl;

    // Compare the time taken by Quadratic Probing
    start = chrono::high_resolution_clock::now();
    quadratic_probing.search(4);
    end = chrono::high_resolution_clock::now();
    // Calculate the time taken
    duration = end - start;
    cout << "Search operation time for Quadratic Probing: \t" << duration.count() << " milli seconds." << endl;

    // Compare the time taken by Double Hashing 
    start = chrono::high_resolution_clock::now();
    double_hashing.search(4);
    end = chrono::high_resolution_clock::now();
    // Calculate the time taken
    duration = end - start;
    cout << "Search operation time for Double Hashing: \t" << duration.count() << " milli seconds." << endl;
} S
*/