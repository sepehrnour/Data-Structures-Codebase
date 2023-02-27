#include <iostream>
using namespace std;

class MyArray 
{
public:
    static int s_Search(int arr[], int n, int value) 
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
};

int main() 
{
    int arr[] = {1, 2, 3, 4, 5}; // array definition and value assignment to index position
    int n = sizeof(arr)/sizeof(arr[0]); // sizeof(arr) in bytes / sizeof(arr[0]) in bytes = number of elements in arr - sizeof when used on an array yields the byte value of the array in return
    int value = 3; // search value, can be changed to search for other values

    MyArray obj;
    int result = obj.s_Search(arr, n, value);

    if (result == -1) 
    {
        cout << "Value not found in array" << endl;
    } 
    else 
    {
        cout << "Value found at index: " << result << endl;
    }

    return 0;
}