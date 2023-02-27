#include <iostream>
using namespace std;

class MyArray 
{
public:
    static int Search(int arr[], int n, int value) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (arr[i] == value) 
            {
                return i;
            }
        }
        return -1;
    }

    static void SpawnSort() 
    {
        int n;
        cout << "Enter the number of indices: ";
        cin >> n;
        int arr[n];
        for (int i = 0; i < n; i++) 
        {
            cout << "Enter a number for index " << i << ": ";
            cin >> arr[i];
        }
        int value;
        cout << "Enter the value to search for: ";
        cin >> value;
        int result = Search(arr, n, value);
        cout << result;
    }
};

int main() 
{
    MyArray::SpawnSort();
    return 0;
}