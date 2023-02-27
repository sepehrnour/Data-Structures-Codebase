#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    // Default constructor
    Node()
    {
        data = 0;
        next = NULL;
    }

    // Parameterised Constructor
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class LinkedList
{
public:
    Node *head;
    LinkedList()
    {
        head = NULL;
    }
    void insertAtFront(int data)
    {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }
    void printList()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void readList()
    {
        int n;
        while (true)
        {
            cout << "Enter a number (-1 to end): ";
            cin >> n;
            if (n == -1)
            {
                break;
            }
            insertAtFront(n);
            printList();
        }
    }
};

int main()
{
    LinkedList ll;
    ll.readList();
    return 0;
}