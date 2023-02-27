#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

class SortedLinkedList {
public:
    Node* head;
    SortedLinkedList() {
        head = NULL;
    }

    void createAndSort() {
        int value;
        cout << "Enter elements to sort (Enter -1 to stop): " << endl;
        cin >> value;
        while (value != -1) {
            addNode(value);
            cin >> value;
        }

        cout << "Sorted Linked List: ";
        Node* current = head;
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
    }

    void addNode(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            return;
        }

        Node* current = head;
        Node* prev = NULL;
        while (current != NULL && current->data < value) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            newNode->next = head;
            head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
};

int main() {
    SortedLinkedList list;
    list.createAndSort();
    return 0;
}