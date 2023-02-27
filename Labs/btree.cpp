#include <iostream>

using namespace std;

class BinaryTree {
private:
    int* data; // array to store the tree data
    int count; // current number of nodes in the tree
public:
    BinaryTree() : data(nullptr), count(0) {}
    ~BinaryTree() { delete[] data; }
    
    void add(int value) {
        int* newData = new int[count + 1]; // allocate new memory for the updated array
        for (int i = 0; i < count; i++) {
            newData[i] = data[i]; // copy existing data
        }
        newData[count] = value; // add new value to the end
        delete[] data; // free old memory
        data = newData; // update pointer to the new array
        count++; // increase count
    }
    
    void print() {
        cout << "Binary Tree:\n";
        for (int i = 0; i < count; i++) {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    BinaryTree tree;
    tree.add(5);
    tree.add(3);
    tree.add(7);
    tree.add(1);
    tree.print();
    return 0;
}
