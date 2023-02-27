#include <iostream>
using namespace std;

const int MaxSize = 10;

class Queue 
{
    public:
        int arr[MaxSize];
        int Count;
        int Front;
        int Back;

        Queue() 
        {
            Count = 0;
            Front = 0;
            Back = -1;
        }

        bool IsEmpty() 
        {
            return Count == 0;
        }

        bool Enqueue(int num) 
        {
            if (Count == MaxSize) 
            {
                cout << "Queue is full." << endl;
                return false;
            } else 
            {
                Back = (Back + 1) % MaxSize;
                arr[Back] = num;
                Count++;
                return true;
            }
        }

        int Dequeue() 
        {
            if (IsEmpty()) 
            {
                cout << "Queue is empty." << endl;
                return -1;
            } 
            else 
            {
                int frontNum = arr[Front];
                Front = (Front + 1) % MaxSize;
                Count--;
                return frontNum;
            }
        }
};

int main() 
{
    Queue q;

    for (int i = 1; i <= 10; i++) 
    {
        if (q.Enqueue(i))
        {
            cout << i << " enqueued." << endl;
        }
    }

    //Full queue test
    //q.Enqueue(11);

    for (int i = 1; i <= 10; i++) 
    {
    cout << q.Dequeue() << " dequeued." << endl;
    }

    //Empty queue test
    //q.Dequeue();

    return 0;
}