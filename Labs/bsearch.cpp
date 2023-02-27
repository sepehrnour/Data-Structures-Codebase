#include <iostream>
using namespace std;

class binary_search
{
public:
    int BinarySearch(int Array[], int Length, int value)
    {
        int left = 0;
        int right = Length - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (Array[mid] == value)
            {
                return mid;
            }
            else if (Array[mid] < value)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return -1;
    }
};

int main()
{
    //Array to search definition
    int arr[] = {1, 2, 3, 4, 5};
    //Finding length of array through byte size of full array / byte size of a single index - giving us the amount of indexes 
    int len = sizeof(arr) / sizeof(arr[0]);
    //Value to be searched for, changing this value will change the target for the binary search, yielding the index value of the specified target(if it exists)
    int value = 3;
    //Class instantiating
    binary_search bs;
    //Call and return class method binary 
    cout << bs.BinarySearch(arr, len, value) << endl;
    return 0;
}