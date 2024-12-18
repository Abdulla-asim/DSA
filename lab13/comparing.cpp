#include <iostream>
#include <vector>
#include "/workspaces/DSA/lab12/compare.cpp"

using namespace std;
using namespace std::chrono;

class CuckooHashing
{
private:
    std::vector<int> table_1, table_2;
    int table_size;

    // Hash functions
    int h1(int key)
    {
        return key % table_size;
    }

    int h2(int key)
    {
        return (key / table_size) % table_size;
    }

    // Function to perform cuckoo insert in table_1
    bool insert_into_table_1(int key)
    {
        int index = h1(key);
        if (table_1[index] == -1)
        {
            table_1[index] = key;  // Insert the key into table_1
            return true;
        }
        else
        {
            // Displace the existing key in table_1 and insert the new key
            int displaced_key = table_1[index];
            table_1[index] = key;
            return insert_into_table_2(displaced_key);
        }
    }

    // Function to perform cuckoo insert in table_2
    bool insert_into_table_2(int key)
    {
        int index = h2(key);
        if (table_2[index] == -1)
        {
            table_2[index] = key;  // Insert the key into table_2
            return true;
        }
        else
        {
            // Displace the existing key in table_2 and insert the new key
            int displaced_key = table_2[index];
            table_2[index] = key;
            return insert_into_table_1(displaced_key);
        }
    }

public:
    CuckooHashing(int size)
    {
        table_size = size;
        table_1.resize(size, -1);
        table_2.resize(size, -1);
    }

    // Insert a key into the cuckoo hashing table
    void insert(int key)
    {
        if (!insert_into_table_1(key))
        {
            std::cout << "Insertion failed!" << std::endl;
        }
    }

    // Check if a key exists in the cuckoo hashing table
    bool exists(int key)
    {
        int index_1 = h1(key);
        int index_2 = h2(key);
        return table_1[index_1] == key || table_2[index_2] == key;
    }

    // Remove a key from the cuckoo hashing table
    void remove(int key)
    {
        int index_1 = h1(key);
        int index_2 = h2(key);

        if (table_1[index_1] == key)
        {
            table_1[index_1] = -1;  // Remove from table_1
        }
        else if (table_2[index_2] == key)
        {
            table_2[index_2] = -1;  // Remove from table_2
        }
        else
        {
            std::cout << "Key not found!" << std::endl;
        }
    }
};

int main()
{
    // Compare all types of addressing
    HashTable_DA direct_addressing = HashTable_DA(13);
    HashTable_LP linear_probing = HashTable_LP(13);
    HashTable_QP quadratic_probing = HashTable_QP(13);
    HashTable_DH double_hashing = HashTable_DH(13);
    CuckooHashing cuckoo_hashing = CuckooHashing(5);

    // Add pairs to all tables
    direct_addressing.insert(1, 10);
    direct_addressing.insert(2, 20);
    linear_probing.insert(1, 10);
    linear_probing.insert(2, 20);
    quadratic_probing.insert(1, 10);
    quadratic_probing.insert(2, 20);
    double_hashing.insert(1, 10);
    double_hashing.insert(2, 20);
    cuckoo_hashing.insert(1);
    cuckoo_hashing.insert(2);

    // Search for pairs in all tables keeping track of time taken
    auto start = high_resolution_clock::now();
    direct_addressing.search(1);
    auto end = high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    std::cout << "Time taken for Direct Addressing: " << duration.count() << " ms" << std::endl;

    start = high_resolution_clock::now();
    linear_probing.search(1);
    end = high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken for Linear Probing: " << duration.count() << " ms" << std::endl;

    start = high_resolution_clock::now();
    quadratic_probing.search(1);
    end = high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken for Quadratic Probing: " << duration.count() << " ms" << std::endl;

    start = high_resolution_clock::now();
    double_hashing.search(1);
    end = high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken for Double Hashing: " << duration.count() << " ms" << std::endl;

    start = high_resolution_clock::now();
    cuckoo_hashing.exists(1);
    end = high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken for Cuckoo Hashing: " << duration.count() << " ms" << std::endl;
}
