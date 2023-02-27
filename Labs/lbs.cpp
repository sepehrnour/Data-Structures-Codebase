#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top;
    int count;
public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    ~Stack() {
        while (!IsEmpty()) {
            Pop();
        }
    }

    void Push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
        count++;
    }

    int Pop() {
        if (IsEmpty()) {
            cout << "Error: Stack is empty." << endl;
            return -1;
        }
        int data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
        return data;
    }

    bool IsEmpty() {
        return count == 0;
    }
};

int main() {
    Stack myStack;

    int input;
    cout << "Enter integers continously to push onto the stack, enter a non-integer to submit:" << endl;
    while (cin >> input) {
        myStack.Push(input);
    }

    cout << "Popping from the stack:" << endl;
    while (!myStack.IsEmpty()) {
        cout << myStack.Pop() << endl;
    }

    return 0;
}
