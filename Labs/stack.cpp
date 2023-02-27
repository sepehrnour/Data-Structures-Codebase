#include <iostream>

using namespace std;

class Stack
{
private:
    const int MaxSize = 10;
    int items[10];
    int count;

public:
    Stack() { count = 0; }
    void Push(int value)
    {
        if (count == MaxSize)
        {
            cout << "Error: Stack is full" << endl;
            return;
        }
        items[count++] = value;
    }

    int Pop()
    {
        if (IsEmpty())
        {
            cout << "Error: Stack is empty" << endl;
            return -1;
        }
        return items[--count];
    }

    bool IsEmpty()
    {
        return count == 0;
    }
};

int main()
{
    Stack myStack;
    for (int i = 1; i <= 10; i++)
    {
        myStack.Push(i);
        cout << i << " pushed" << endl;
    }

    //Full stack test
    //myStack.Push(11);

    while (!myStack.IsEmpty())
    {
        cout << myStack.Pop() << " popped" << endl;
    }

    //Empty stack test
    //myStack.Pop();

    return 0;
}