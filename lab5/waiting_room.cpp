#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Queue {
private:
    T* queue;
    int front;
    int rear;
    int size;

public:
    Queue(int size) {
        this->size = size;
        queue = new T[size];
        front = -1;
        rear = -1;
    }

    ~Queue() {
        delete[] queue;
    }

    void enqueue(T value) {
        if (is_full()) {
            cout << "Queue is full" << endl;
            return;
        }
        queue[++rear] = value;
    }

    T dequeue() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        return queue[++front];
    }

    bool is_empty() {
        return front == rear;
    }

    bool is_full() {
        return rear == size - 1;
    }

    void clear() {
        front = rear = -1;
    }

    T peek() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
            return T(); // Return default value of T
        }
        return queue[front + 1];
    }

    void display() {
        if (is_empty()) {
            cout << "Queue is empty" << endl;
        } else {
            for (int i = front + 1; i <= rear; i++) {
                cout << queue[i];
            }
            cout << endl;
        }
    }
};

class Patient {
private:
    string name;
    static int id_counter;
    int id;

public:
    Patient() {
        this->name = "";
        this->id = id_counter++;
    }

    Patient(string name) {
        this->name = name;
        this->id = id_counter++;
    }

    string get_name() const {
        return name;
    }

    int get_id() const {
        return id;
    }

    // Overload the << operator for easy printing
    friend ostream& operator<<(ostream& os, const Patient& patient) {
        os << "Patient ID: " << patient.id << ", Name: " << patient.name << endl;
        return os;
    }
};

// Initialize static member
int Patient::id_counter = 0;

class WaitingRoom {
private:
    Queue<Patient>* queue;

public:
    WaitingRoom(int size) {
        queue = new Queue<Patient>(size);
    }

    ~WaitingRoom() {
        delete queue;
    }

    void register_patient(const Patient& patient) {
        queue->enqueue(patient);
    }

    void serve_patient() {
        Patient patient = queue->dequeue();
        if (queue->is_empty()) {
            cout << "No patients in the waiting room" << endl;
            return;
        }
        if (patient.get_name() != "") {
            cout << "Serving " << patient << endl;
        }
    }

    void display_patients() {
        queue->display();
    }
};

int main() {
    WaitingRoom wr(5);

    wr.register_patient(Patient("Alice"));
    wr.register_patient(Patient("Bob"));
    wr.register_patient(Patient("Charlie"));

    wr.display_patients();

    wr.serve_patient();
    wr.serve_patient();
    
    cout << "Remaining Patients:" << endl;
    wr.display_patients();

    return 0;
}