#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
class RPN
{
public:
    void evaluateExpression()
    {
        while (true)
        {
            cout << "Enter a Reverse Polish expression, terminated by '=': ";
            string input;
            getline(cin, input);
            if (input == "0")
            {
                break;
            }
            stack<double> s;
            stringstream ss(input);
            string token;
            while (ss >> token)
            {
                if (token == "+")
                {
                    if (s.size() < 2)
                    {
                        cout << "Error: Too many operators" << endl;
                        break;``````
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
                        cout << "Error: Too many operators" << endl;
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
                        cout << "Error: Too many operators" << endl;
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
                        cout << "Error: Too many operators" << endl;
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
        }
    }
};

int main()
{
    RPN rpn;
    rpn.evaluateExpression();
    return 0;
}