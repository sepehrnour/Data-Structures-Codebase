#include <iostream>
using namespace std;

class DynamicArray
{
public:
    void loadAndPrintArray()
    {
        int size;
        cout << "Enter the size of the array: ";
        cin >> size;

        int *arr = new int[size]; // declare a dynamically allocated array of integers
        int i = 0;
        int input;
        cout << "Enter a number for index " << i << ": ";
        cin >> input;

        while (input != -1)
        {
            if (i >= size)
            {
                // expand the array if it has reached its maximum size
                int *temp = new int[size * 2];
                for (int j = 0; j < size; j++)
                {
                    temp[j] = arr[j];
                }
                delete[] arr;
                arr = temp;
                size = size * 2;
            }
            arr[i] = input;
            i++;
            cout << "Enter a number for index " << i << ": ";
            cin >> input;
        }

        cout << "The array contains: ";
        for (int j = 0; j < i; j++)
        {
            cout << arr[j] << " ";
        }
        delete[] arr;
    }
};

int main()
{
    DynamicArray darray;
    darray.loadAndPrintArray();
    return 0;
}