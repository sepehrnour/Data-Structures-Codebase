#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class BinarySearchTree
{
public:
    Node *root;

    BinarySearchTree()
    {
        root = NULL;
    }

    void add(int data)
    {
        Node *newNode = new Node(data);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        Node *current = root;

        while (true)
        {
            if (data < current->data)
            {
                if (current->left == NULL)
                {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            }
            else
            {
                if (current->right == NULL)
                {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }

    void printInorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        printInorder(node->left);
        cout << node->data << " ";
        printInorder(node->right);
    }

    void print()
    {
        printInorder(root);
        cout << endl;
    }
};

int main()
{
    BinarySearchTree bst;

    bst.add(5);
    bst.add(3);
    bst.add(7);
    bst.add(1);
    bst.add(9);

    bst.print();

    return 0;
}