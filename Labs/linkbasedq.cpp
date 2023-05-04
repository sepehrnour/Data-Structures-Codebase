#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};

class Queue
{
private:
    Node *front;
    Node *rear;
    int count;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    void Enqueue(int d)
    {
        Node *temp = new Node(d);
        if (front == NULL)
        {
            front = temp;
        }
        else
        {
            rear->next = temp;
        }
        rear = temp;
        count++;
    }

    int Dequeue()
    {
        if (front == NULL)
        {
            cout << "Error: Queue is empty." << endl;
            return -1;
        }
        Node *temp = front;
        int data = temp->data;
        front = front->next;
        delete temp;
        count--;
        return data;
    }

    bool IsEmpty()
    {
        return (count == 0);
    }
};

int main()
{
    Queue myQueue;

    myQueue.Enqueue(10);
    myQueue.Enqueue(20);
    myQueue.Enqueue(30);

    int front = myQueue.Dequeue();
    cout << "Dequeued item: " << front << endl;

    cout << "Is the queue empty? " << (myQueue.IsEmpty() ? "Yes" : "No") << endl;

    myQueue.Enqueue(40);
    myQueue.Enqueue(50);
    front = myQueue.Dequeue();
    cout << "Dequeued item: " << front << endl;

    cout << "Is the queue empty? " << (myQueue.IsEmpty() ? "Yes" : "No") << endl;

    return 0;
}
