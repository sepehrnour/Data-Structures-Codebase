#include <iostream>
using namespace std;


class SimpleArray {
public:
    void loadAndPrintArray() {
        int arr[5]; // declare an array of 5 integers
        for(int i = 0; i < 5; i++) {
            cout << "Enter a number for index " << i << ": ";
            cin >> arr[i];
        }
        cout << "The array contains: ";
        for(int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
    }
};

int main() {
    SimpleArray sarray;
    sarray.loadAndPrintArray();
    return 0;
}