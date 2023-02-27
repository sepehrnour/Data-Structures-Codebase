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

    void preorder(int index = 0) {
        if (index >= count) {
            return;
        }
        cout << data[index] << " ";
        preorder(2 * index + 1);
        preorder(2 * index + 2);
    }

    void inorder(int index = 0) {
        if (index >= count) {
            return;
        }
        inorder(2 * index + 1);
        cout << data[index] << " ";
        inorder(2 * index + 2);
    }

    void postorder(int index = 0) {
        if (index >= count) {
            return;
        }
        postorder(2 * index + 1);
        postorder(2 * index + 2);
        cout << data[index] << " ";
    }
};

int main() {
    BinaryTree tree;
    tree.add(5);
    tree.add(3);
    tree.add(7);
    tree.add(1);
    tree.add(4);
    tree.add(6);
    tree.add(9);
    tree.print();
    cout << "Preorder traversal:\n";
    tree.preorder();
    cout << "\nInorder traversal:\n";
    tree.inorder();
    cout << "\nPostorder traversal:\n";
    tree.postorder();
    cout << endl;
    return 0;
}
