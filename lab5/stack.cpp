#include <iostream>

using namespace std;

class Stack {
    private:
        char *stack;
        int top;
        int size;
    public:
        Stack(int size) {
            this->size = size;
            stack = new char[size];
            top = -1;
        }
        void push(int value) {
            if (top == size - 1) {
                cout << "Stack is full" << endl;
            } else {
                stack[++top] = value;
            }
        }

        char pop() {
            if (top == -1) {
                cout << "Stack is empty" << endl;
                return -1; 
            }
            return stack[top--];
        }

        bool is_empty() {
            return top == -1;
        }

        bool is_full() {
            return top == size - 1;
        }

        void clear() {
            for (int i = size - 1; i >= 0; i--) {
                delete &stack[i];
            }
        }

        char peek() {
            if (top == -1) {
                cout << "Stack is empty" << endl;
            }
            return stack[top];
        }

        void display() {
            if (top == -1) {
                cout << "Stack is empty" << endl;
            } else {
                cout << "Stack elements: ";
                for (int i = 0; i <= top; i++) {
                    cout << stack[i] << " ";
                }
                cout << endl;
            }
        }

        ~Stack() {
            delete[] stack;
        }
};

int main() {
    // cheking complete opening and closing of brackets
    string expression;
    do {
        cout << "Enter an expression: (q to quit)" << endl;
        getline(cin, expression);
        if (expression == "q" || expression == "Q") {
            break;
        }

        Stack stack(expression.length());
        bool balanced = true;
        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
                stack.push(expression[i]);
            } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
                if (stack.is_empty()) {
                    balanced = false;
                    break;
                } 

                

                char top = stack.peek();
                switch(top) {
                    case '(':
                        if (expression[i] == ')') {
                            stack.pop();
                        } else {
                            balanced = false;
                            cout << "Missing ')' at position " << i << endl;
                        }
                        break;
                    case '[':
                        if (expression[i] == ']') {
                            stack.pop();
                        } else {
                            balanced = false;
                            cout << "Missing ']' at position " << i << endl;
                        }
                        break;
                    case '{':
                        if (expression[i] == '}') {
                            stack.pop();
                        } else {
                            balanced = false;
                            cout << "Missing '}' at position " << i << endl;
                        }
                        break;
                }                
            }
        }
        if (balanced && stack.is_empty()) {
            cout << ">>Expression is balanced" << endl;
        } else {
            cout << ">>Expression is not balanced" << endl;
        }
        cout << endl;
    } while(true);
    // destructor will be called here

    return 0;
}