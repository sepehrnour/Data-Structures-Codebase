#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int weight;
    Node *nextWeight;
    Node *nextName;
    Node(string name, int weight)
    {
        this->name = name;
        this->weight = weight;
        nextWeight = nullptr;
        nextName = nullptr;
    }
};

class DoublyLinkedList
{
private:
    Node *headWeight;
    Node *headName;
public:
    DoublyLinkedList()
    {
        headWeight = nullptr;
        headName = nullptr;
    }
    ~DoublyLinkedList()
    {
        while (!IsEmpty())
        {
            Pop();
        }
    }

    void Insert(string name, int weight)
    {
        Node *newNode = new Node(name, weight);

        // Insert based on weight
        if (headWeight == nullptr || weight < headWeight->weight)
        {
            newNode->nextWeight = headWeight;
            headWeight = newNode;
        }
        else
        {
            Node *temp = headWeight;
            while (temp->nextWeight != nullptr && temp->nextWeight->weight < weight)
            {
                temp = temp->nextWeight;
            }
            newNode->nextWeight = temp->nextWeight;
            temp->nextWeight = newNode;
        }

        // Insert based on name
        if (headName == nullptr || name < headName->name)
        {
            newNode->nextName = headName;
            headName = newNode;
        }
        else
        {
            Node *temp = headName;
            while (temp->nextName != nullptr && temp->nextName->name < name)
            {
                temp = temp->nextName;
            }
            newNode->nextName = temp->nextName;
            temp->nextName = newNode;
        }
    }

    void PrintByWeight()
    {
        Node *temp = headWeight;
        cout << "Names & weights sorted(ascending) by weight: ";
        while (temp != nullptr)
        {
            cout << temp->name << " - " << temp->weight << ", ";
            temp = temp->nextWeight;
        }
        cout << endl;
    }

    void PrintByName()
    {
        Node *temp = headName;
        cout << "Names & weights sorted(ascending) by name: ";
        while (temp != nullptr)
        {
            cout << temp->name << " - " << temp->weight << ", ";
            temp = temp->nextName;
        }
        cout << endl;
    }

    bool IsEmpty()
    {
        return headWeight == nullptr && headName == nullptr;
    }

    void Pop()
    {
        if (IsEmpty())
        {
            cout << "Error: List is empty." << endl;
            return;
        }

        Node *temp = headWeight;
        headWeight = headWeight->nextWeight;
        headName = headName->nextName;
        delete temp;
    }
};
int main()
{
    DoublyLinkedList DList;
    string name;
    int weight;
    cout << "Enter names and weights continuously for up to 15 people:" << endl;
    for (int i = 0; i < 15; i++)
    {
        cin >> name >> weight;
        DList.Insert(name, weight);
    }

    DList.PrintByName();
    DList.PrintByWeight();

    return 0;
}