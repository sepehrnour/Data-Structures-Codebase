#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class Node
{
public:
    double data;
    Node *next;
    Node(double data) : data(data), next(NULL) {}
};

class LinkedStack
{
private:
    Node *head;
    int size_;

public:
    LinkedStack() : head(NULL), size_(0) {}

    void push(double data)
    {
        Node *temp = new Node(data);
        temp->next = head;
        head = temp;
        size_++;
    }

    double pop()
    {
        if (head == NULL)
        {
            cout << "Error: Linked stack is empty" << endl;
            return 0;
        }

        Node *temp = head;
        head = head->next;
        double data = temp->data;
        delete temp;
        size_--;
        return data;
    }

    int size()
    {
        return size_;
    }

    bool isEmpty()
    {
        return head == NULL;
    }

    double top()
    {
        if (head == NULL)
        {
            cout << "Error: Stack is empty" << endl;
            return 0;
        }

        return head->data;
    }
};

class RPN
{
public:
    void evaluateExpression()
    {
        cout << "Enter a Reverse Polish expression, terminated by '=': ";
        string input;
        getline(cin, input);

        LinkedStack s;
        stringstream ss(input);
        string token;
        int operatorCount = 0;

        while (ss >> token)
        {
            if (token == "+")
            {
                if (s.size() < 2)
                {
                    cout << "Error: Too few operators" << endl;
                    break;
                }
                double b = s.top();
                s.pop();
                double a = s.top();
                s.pop();
                s.push(a + b);
            }
            else if (token == "-")
            {
                if (s.size() < 2)
                {
                    cout << "Error: Too few operators" << endl;
                    break;
                }
                double b = s.top();
                s.pop();
                double a = s.top();
                s.pop();
                s.push(a - b);
            }
            else if (token == "*")
            {
                if (s.size() < 2)
                {
                    cout << "Error: Too few operators" << endl;
                    break;
                }
                double b = s.top();
                s.pop();
                double a = s.top();
                s.pop();
                s.push(a * b);
            }
            else if (token == "/")
            {
                if (s.size() < 2)
                {
                    cout << "Error: Too few operators" << endl;
                    break;
                }
                double b = s.top();
                s.pop();
                double a = s.top();
                s.pop();
                if (b == 0)
                {
                    cout << "Error: Division by zero" << endl;
                    break;
                }
                s.push(a / b);
            }
            else if (token == "=")
            {
                if (s.size() > 1)
                {
                    cout << "Error: Too many operands" << endl;
                    break;
                }
                cout << fixed << s.top() << endl;
                break;
            }
            else
            {
                s.push(stod(token));
            }
        }
    evaluateExpression();
    }
};

int main()
{
    RPN rpn;
    rpn.evaluateExpression();
    return 0;
}