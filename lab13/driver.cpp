#include <iostream>
#include <string>
#include <vector>

using namespace::std;


struct DriverInfo 
{
    string name;
    string vehicle;
    float rating;
};

struct Driver 
{
    string id;
    DriverInfo info;
};

class DriverHashTable 
{
    private:
        vector<Driver> *table;
        int size;
    public:
        DriverHashTable(int size) 
        {
            this->size = size;
            table = new vector<Driver>[size];
        }

        int hash(string key) 
        {
            int hash = 0;
            for (char c : key) 
                hash = ((49 * hash) + c) % size;
            return hash;
        }

        bool searchDriver(string driver_id) 
        {
            int index = hash(driver_id);
            for (Driver driver : table[index])
                if (driver.id == driver_id) 
                {
                    cout << "Driver's id: " << driver.id << endl;
                    cout << "Driver Name: " << driver.info.name << endl;
                    cout << "Driver's Vehicle: " << driver.info.vehicle << endl;
                    cout << "Driver Rating: " << driver.info.rating << endl;
                    return true;
                }
            cout << "A driver with id " << driver_id << " was not found." << endl;
            return false;
        }

        void addDriver(string driver_id, DriverInfo driverInfo) 
        {
            table[hash(driver_id)].push_back({driver_id, driverInfo});
        }

        void removeDriver(string driver_id) 
        {
            int index = hash(driver_id);
            for (int i = 0; i < table[index].size(); i++)
                if (table[index][i].id == driver_id) 
                {
                    table[index].erase(table[index].begin() + i);
                    cout << "The driver with Driver id " << driver_id << " has been removed." << endl;
                    return;
                }
            cout << "A driver with id " << driver_id << " was not found." << endl;
        }
};

int main() 
{
    DriverHashTable hashmap(25);
    int choice;
    do 
    {
        cout << "----------------------------"<< endl;
        cout << "1. Add Driver" << endl;
        cout << "2. Search Driver" << endl;
        cout << "3. Remove Driver" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------------"<< endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string driver_id;
        DriverInfo driverInfo;

        switch (choice) {
            case 1:
                cout << "Driver id: ";
                cin >> driver_id;
                cout << "Driver Name: ";
                cin.ignore();
                getline(cin, driverInfo.name);
                cout << "Vehicle: ";
                getline(cin, driverInfo.vehicle);
                cout << "Rating: ";
                cin >> driverInfo.rating;
                hashmap.addDriver(driver_id, driverInfo);
                break;
            case 2:
                cout << "Driver id: ";
                cin >> driver_id;
                hashmap.searchDriver(driver_id);
                break;
            case 3:
                cout << "Driver id: ";
                cin >> driver_id;
                hashmap.removeDriver(driver_id);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}