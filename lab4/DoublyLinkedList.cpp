#include <iostream>

using namespace::std;

class Node {
    public:
        int data;
        Node *next;
        Node *prev;
};

class DoublyLinkedList {
    public:
        Node *head;
        Node *tail;

        Node* prev_node; // The previous node to the current node while doing operations
        Node* current_node; // Current node in focus while doing operations

        // Constructors
        DoublyLinkedList() {
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
            // in case of` an empty list
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            }
            // in case of a non-empty list
            else {
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            }
        }

        void insert_at_end(int data) {
            Node *new_node = new Node();

            new_node->data = data;
            // in case of an empty list
            if (tail == NULL) {
                tail = new_node;
                head = new_node;
            }
            else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        }

        void print_list() {
            Node *temp = head;
            // if the list is not empty
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

            // Traverse the list to find the value
            while (current_node != NULL && current_node->data < value) {
                prev_node = current_node;
                current_node = current_node->next;
            }
            // Check if the value is found
            if (current_node != NULL && current_node->data == value) {
                return 1; // FOUND
            }
            current_node = NULL;
            return 0; // NOT FOUND
        }

        void insert_node(int value) {
            Node * new_node = new Node();
            new_node->data = value;
            // if the value already exists in the list
            if (search(value) == 1) {
                cout << "The value " << value << " already exists in the linked list.";
                return;
            }
            // Insert the value in the list
            else {
                // if location is at the front
                if (prev_node == NULL) 
                    insert_at_front(value);
                // if location is not at the front
                else {
                    new_node->next = prev_node->next;
                    new_node->prev = prev_node;
                    prev_node->next->prev = new_node;
                    prev_node->next = new_node;
                    if (new_node->next == NULL) tail = new_node;
                }
            }
        }

        void delete_front_node() {
            if (!is_empty()) {
                Node * temp = head;
                head = head-> next;
                head->prev = NULL;
                delete temp;
            }
        }

        void delete_last_node() {
            if (!is_empty()) {
                Node * temp = tail;
                tail = tail->prev;
                tail->next = NULL;
                delete temp;
            }
        }

        void delete_node(int value) {
            // return if the list is empty
            if (is_empty())
                return;
            // search for the value in the list
            if (search(value)) {
                if (current_node == head && prev_node == NULL) {
                    delete_front_node();
                }
                else if(current_node->next == NULL) {
                    delete_last_node();
                }
                else {
                    prev_node->next = current_node->next;
                    current_node->next->prev = prev_node;
                    delete current_node;
                }
            }
        }

        void destroy_list() {
            Node *temp = NULL;
            // Traverse the list and delete each node until NULL
            while(head) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }

        void reverse_list() {
            Node *current = head;
            Node *temp = NULL;
            while (current != NULL) {
                // Swap the next and prev pointers of the current node
                temp = current->prev;
                current->prev = current->next;
                current->next = temp;
                current = current->prev; // going to the next node (but since next and prev are reversed)
            }
            // Swap the head and tail pointers
            tail = head;
            head = temp->prev;
        }

        void swap(int val_1, int val_2) {
            // Search for the values in the list
            int found_1 = search(val_1);
            Node *node1 = current_node;
            int found_2 = search(val_2);
            Node *node2 = current_node;

            // If both values are same, return
            if (node1 == node2)
                return;

            if (found_1 == 1 && found_2 == 1) 
            {
                // Set the previous and next nodes of the nodes that need to be swapped
                if (node1->prev != NULL) node1->prev->next = node2;
                if (node2->prev != NULL) node2->prev->next = node1;
                if (node1->next != NULL) node2->next->prev = node2;
                if (node2->next != NULL) node2->next->prev = node1;

                // Swap the prev and next of the target pointers
                Node *tempPrev = node1->prev;
                Node *tempNext = node1->next;

                node1->prev = node2->prev;
                node1->next = node2->next;

                node2->next = tempNext;
                node2->prev = tempPrev; 

                // set the head in case of first node
                if (head == node1) head = node2;
                else if (head == node2) head = node1;
                
                // Set the tail in case of last node
                if (tail == node1) tail = node2;
                else if (tail == node2) tail = node1;

            }
            else {
                // If the values are not found, return
                cout << "Values not found." << endl;
                return;
            }
        }

        void group_even_odd() {
            Node *even_head = NULL, *even_tail = NULL;
            Node *odd_head = NULL, *odd_tail = NULL;
            Node *current = head;

            while (current != NULL) {
                Node *next_node = current->next; // Save the next node
                Node *prev_node = current->prev; // Save the previous node
                current->next = NULL; // Disconnect the current node from the list
                current->prev = NULL;

                // if the current node is even 
                if (current->data % 2 == 0) {
                    // Append to even list
                    if (even_head == NULL) {
                        even_head = even_tail = current;
                    } else {
                        even_tail->next = current;
                        current->prev = even_tail;
                        even_tail = current;
                    }
                } else { // Current node is odd
                    // Append to odd list
                    if (odd_head == NULL) {
                        odd_head = odd_tail = current;
                    } else {
                        odd_tail->next = current;
                        current->prev = odd_tail;
                        odd_tail = current;
                    }
                }
                current = next_node; // Move to the next node
            }

            // Connect even list to odd list
            if (even_tail != NULL) {
                even_tail->next = odd_head;
                odd_head->prev = even_tail;
                head = even_head;
            } else {
                head = odd_head;
            }

            // Update the tail
            if (odd_tail != NULL) {
                tail = odd_tail;
            } else {
                tail = even_tail;
            }
        }
};

int main() {
    DoublyLinkedList list;
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
        cout << "9: REVERSE THE LIST" << endl;
        cout << "10: SWAP NODES" << endl;
        cout << "11: GROUP ODD AND EVEN ELEMENTS" << endl;
        cout << "0: Exit" << endl;
        cout << "> ";
        cin >> input;

        while (input < 0 || input > 11) {
            cout << "ERROR: Enter correct input 0 to 11: ";
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
            
            case 9:
                cout << "List is being reversed..." << endl;
                list.reverse_list();
                list.print_list();
                break;

            case 10:
                cout << "Enter two values to be swapped: ";
                int a, b;
                cin >> a >> b;
                list.swap(a, b);
                cout << "Swapping elements..." << endl;
                list.print_list();
                break;

            case 11:
                cout << "Grouping odd and even elements..." << endl;
                list.group_even_odd();
                list.print_list();
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } 

    return 0;
}
