#include <iostream>

using namespace::std;

class Node {
    public:
        int data;
        Node *next;
};

class LinkedList {
    public:
        Node *head;
        Node *tail;

        Node* prev_node; // The previous node to the current node while doing operations
        Node* current_node; // Current node in focus while doing operations

        // Constructors
        LinkedList() {
                head = NULL;
                tail = NULL;
                prev_node = NULL;
                current_node = NULL;
        }

        bool is_empty() {
            return (head == NULL);
        }

        // Inserts a node at the front of the linked list
        void insert_at_front(int data) {
            Node *new_node = new Node();

            new_node->data = data;
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            }
            else {
                new_node->next = head;
                head = new_node;
            }
        }

        void insert_at_end(int data) {
            Node *new_node = new Node();

            new_node->data = data;
            if (tail == NULL) {
                tail = new_node;
                head = new_node;
            }
            else {
                tail->next = new_node;
                tail = new_node;
            }
        }

        void print_list() {
            Node *temp = head;

            
            if (!is_empty()) {
                cout << "[ ";
                while(temp) {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << "]";
            }
        }

        int search(int value) {
            current_node = head;
            prev_node = NULL;

            while (current_node != NULL && current_node->data < value) {
                prev_node = current_node;
                current_node = current_node->next;
            }

            if (current_node != NULL && current_node->data == value) {
                return 1; // FOUND
            }
            current_node = NULL;
            return 0; // NOT FOUND
        }

        void insert_node(int value) {
            Node * new_node = new Node();
            new_node->data = value;

            if (search(value) == 1) {
                cout << "The value " << value << " already exists in the linked list.";
                return;
            }
            else {
                if (prev_node == NULL) 
                    insert_at_front(value);
                else {
                    new_node->next = prev_node->next;
                    prev_node->next = new_node;
                    if (new_node->next == NULL) tail = new_node;
                }
            }
        }

        void delete_node(int value) {
            if (search(value)) {
                if (current_node == head && prev_node == NULL) {
                    Node *temp = head;
                    head = head->next;
                    delete temp;
                }
                else {
                    prev_node->next = current_node->next;
                    delete current_node;
                }
            }
        }

        void destroy_list() {
            Node *temp = NULL;

            while(head) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }
};

int main() {
    LinkedList list;
    int input = -1;
    int value;

    while (input != 0) {
        cout << "\nWhat do you want to do with the linked list?" << endl;
        cout << "1: Insert value at front" << endl;
        cout << "2: Insert value at end" << endl;
        cout << "3: Insert value in sorted order" << endl;
        cout << "4: Print linked list" << endl;
        cout << "5: Search for a value" << endl;
        cout << "6: Delete a value" << endl;
        cout << "7: Destroy the list" << endl;
        cout << "8: Check if the list is empty" << endl;
        cout << "0: Exit" << endl;
        cout << "> ";
        cin >> input;

        while (input < 0 || input > 8) {
            cout << "ERROR: Enter correct input 0 to 8: ";
            cin >> input;
        }

        switch (input) {
            case 0:
                cout << "Exiting..." << endl;
                break;

            case 1:
                cout << "Enter value to insert at front: ";
                cin >> value;
                list.insert_at_front(value);
                cout << value << " inserted at the front." << endl;
                break;

            case 2:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insert_at_end(value);
                cout << value << " inserted at the end." << endl;
                break;

            case 3:
                cout << "Enter value to insert in sorted order: ";
                cin >> value;
                list.insert_node(value);
                break;

            case 4:
                cout << "Current Linked List: ";
                list.print_list();
                break;

            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                
                if (list.search(value)) {
                    cout << "Value " << value << " found in the list." << endl;
                } else {
                    cout << "Value " << value << " not found in the list." << endl;
                }
                break;

            case 6:
                cout << "Enter value to delete: ";
                cin >> value;
                list.delete_node(value);
                break;

            case 7:
                list.destroy_list();
                cout << "List has been destroyed." << endl;
                break;

            case 8:
                if (list.is_empty()) {
                    cout << "The list is empty." << endl;
                }
                else {
                    cout << "The list is not empty." << endl;
                }
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } 

    return 0;
}