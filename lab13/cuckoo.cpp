#include <iostream>
#include <vector>
using namespace std;

class CuckooHashing
{
private:
    vector<int> table_1, table_2;
    int capacity_1, capacity_2;
    int size_1, size_2;

    int hash_1(int key)
    {
        return key % capacity_1;
    }

    int hash_2(int key)
    {
        return key % capacity_2;
    }

    // Helper function to insert into table_1 or table_2
    bool insert(int key, int table_index)
    {
        if (table_index == 1)
        {
            int index = hash_1(key);
            if (table_1[index] == -1)
            {
                table_1[index] = key;
                size_1++;
                return true;
            }
            else
            {
                int evicted = table_1[index];
                table_1[index] = key;
                if (size_1 >= capacity_1)
                {
                    return false;  // Resize not implemented
                }
                return insert(evicted, 2);  // Evict to table_2
            }
        }
        else if (table_index == 2)
        {
            int index = hash_2(key);
            if (table_2[index] == -1)
            {
                table_2[index] = key;
                size_2++;
                return true;
            }
            else
            {
                int evicted = table_2[index];
                table_2[index] = key;
                if (size_2 >= capacity_2)
                {
                    return false;  // Resize not implemented
                }
                return insert(evicted, 1);  // Evict to table_1
            }
        }
        return false;
    }

public:
    CuckooHashing(int cap_1, int cap_2)
    {
        capacity_1 = cap_1;
        capacity_2 = cap_2;
        table_1.resize(capacity_1, -1);
        table_2.resize(capacity_2, -1);
        size_1 = size_2 = 0;
    }

    bool add_area(int area_id)
    {
        bool inserted = insert(area_id, 1);
        if (!inserted)
        {
            cout << "Table overflow during insertion of " << area_id << endl;
        }
        return inserted;
    }

    // Check if an area ID exists
    bool exists(int area_id)
    {
        int index_1 = hash_1(area_id);
        int index_2 = hash_2(area_id);
        return (table_1[index_1] == area_id || table_2[index_2] == area_id);
    }

    // Remove an area ID
    void remove_area(int area_id)
    {
        int index_1 = hash_1(area_id);
        int index_2 = hash_2(area_id);

        if (table_1[index_1] == area_id)
        {
            table_1[index_1] = -1;
            size_1--;
        }
        else if (table_2[index_2] == area_id)
        {
            table_2[index_2] = -1;
            size_2--;
        }
    }
};

int main()
{
    CuckooHashing cuckoo = CuckooHashing(5, 5);

    cuckoo.add_area(301);
    cuckoo.add_area(401);

    cout << "exists(301): " << (cuckoo.exists(301) ? "true" : "false") << endl; // true
    cout << "exists(501): " << (cuckoo.exists(501) ? "true" : "false") << endl; // false

    cuckoo.remove_area(301);
    cout << "exists(301): " << (cuckoo.exists(301) ? "true" : "false") << endl; // false

    return 0;
}
