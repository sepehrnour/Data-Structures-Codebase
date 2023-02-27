#include <iostream>
#include <vector>
using namespace std;

class VectorArray
{
public:
    void loadAndPrintArray()
    {
        int size;
        cout << "Enter the size of the array: ";
        cin >> size;

        vector<int> arr(size); // declare a vector of integers with size "size"
        for (int i = 0; i < size; i++)
        {
            cout << "Enter a number for index " << i << ": ";
            cin >> arr[i];
        }
        cout << "The array contains: ";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
    }
};

int main()
{
    VectorArray varray;
    varray.loadAndPrintArray();
    return 0;
}