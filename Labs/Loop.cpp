#include <iostream>
using namespace std;

class Summation 
{
public:
    int sum(int n) 
    {
        int result = 0;
        for (int i = 1; i <= n; i++) 
        {
            result += i;
        }
        cout << result;
        return result;
    }
};

int main() 
{
    Summation s;
    int result = s.sum(5); // 15
    return 0;
}