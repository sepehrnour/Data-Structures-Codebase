#include <iostream>
#include <string>
#include <climits>
using namespace std;

struct Node
{
    string name;
    int weight;
    Node *left;
    Node *right;

    Node(string name, int weight)
    {
        this->name = name;
        this->weight = weight;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree
{
private:
    Node *root;

    void insert(Node *&node, string name, int weight)
    {
        if (node == nullptr)
        {
            node = new Node(name, weight);
        }
        else if (name < node->name)
        {
            insert(node->left, name, weight);
        }
        else if (name > node->name)
        {
            insert(node->right, name, weight);
        }
    }

    void preorderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->name << " (" << node->weight << ")" << endl;
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void inorderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            inorderTraversal(node->left);
            cout << node->name << " (" << node->weight << ")" << endl;
            inorderTraversal(node->right);
        }
    }

    void postorderTraversal(Node *node)
    {
        if (node != nullptr)
        {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->name << " (" << node->weight << ")" << endl;
        }
    }

    int getHeight(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    }

    int countLeaves(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else if (node->left == nullptr && node->right == nullptr)
        {
            return 1;
        }
        else
        {
            return countLeaves(node->left) + countLeaves(node->right);
        }
    }

    Node *search(Node *node, string name)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (node->name == name)
        {
            return node;
        }
        else if (name < node->name)
        {
            return search(node->left, name);
        }
        else
        {
            return search(node->right, name);
        }
    }

    int findMinWeight(Node *node)
    {
        if (node == nullptr)
        {
            return INT_MAX;
        }
        int minWeight = node->weight;
        int leftMinWeight = findMinWeight(node->left);
        int rightMinWeight = findMinWeight(node->right);
        if (leftMinWeight < minWeight)
        {
            minWeight = leftMinWeight;
        }
        if (rightMinWeight < minWeight)
        {
            minWeight = rightMinWeight;
        }
        return minWeight;
    }

    Node *findFirstAlphabetical(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            return node;
        }
        else
        {
            return findFirstAlphabetical(node->left);
        }
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
    }

    void insert(string name, int weight)
    {
        insert(root, name, weight);
    }

    void preorderTraversal()
    {
        cout << "Preorder Traversal:" << endl;
        preorderTraversal(root);
    }

    void inorderTraversal()
    {
        cout << "Inorder Traversal:" << endl;
        inorderTraversal(root);
    }

    void postorderTraversal()
    {
        cout << "Postorder Traversal:" << endl;
        postorderTraversal(root);
    }

    int getHeight()
    {
        return getHeight(root);
    }

    int countLeaves()
    {
        return countLeaves(root);
    }

    void search(string name)
    {
        Node *result = search(root, name);
        if (result == nullptr)
        {
            cout << "No match exists." << endl;
        }
        else
        {
            cout << "Name: " << result->name << ", Weight: " << result->weight << endl;
        }
    }

    int findMinWeight()
    {
        return findMinWeight(root);
    }

    string findFirstAlphabetical()
    {
        Node *result = findFirstAlphabetical(root);
        return result != nullptr ? result->name : "";
    }
};

int main()
{
    BinarySearchTree bst;

    for (int i = 0; i < 15; i++)
    {
        string name;
        int weight;
        cout << "Enter name and weight: ";
        cin >> name >> weight;
        bst.insert(name, weight);
    }

    bst.preorderTraversal();
    bst.inorderTraversal();
    bst.postorderTraversal();
    cout << "Height: " << bst.getHeight() << endl;
    cout << "Number of leaves: " << bst.countLeaves() << endl;

    string searchName;
    cout << "Enter a name to search for: ";
    cin >> searchName;
    bst.search(searchName);

    cout << "Minimum weight: " << bst.findMinWeight() << endl;
    cout << "First name in alphabetical order: " << bst.findFirstAlphabetical() << endl;

    return 0;
}
/*
 Enter name and weight: Sepehr 150
 Enter name and weight: Henry 135
 Enter name and weight: Aidan 160
 Enter name and weight: Chaz 145 
 Enter name and weight: Ronny 135 
 Enter name and weight: Jeffrey 190 
 Enter name and weight: Andy 210 
 Enter name and weight: Adam 185 
 Enter name and weight: Collin 150 
 Enter name and weight: Gloria 140 
 Enter name and weight: Marcus 205 
 Enter name and weight: Katie 170 
 Enter name and weight: Marianne 145 
 Enter name and weight: Fareed 170 
 Enter name and weight: Kevin 180 
 Preorder Traversal: 
 Sepehr (150) 
 Henry (135) 
 Aidan (160) 
 Adam (185) 
 Chaz (145) 
 Andy (210) 
 Collin (150) 
 Gloria (140) 
 Fareed (170) 
 Ronny (135) 
 Jeffrey (190) 
 Marcus (205) 
 Katie (170) 
 Kevin (180) 
 Marianne (145) 
 Inorder Traversal: 
 Adam (185) 
 Aidan (160) 
 Andy (210) 
 Chaz (145) 
 Collin (150) 
 Fareed (170) 
 Gloria (140) 
 Henry (135) 
 Jeffrey (190) 
 Katie (170) 
 Kevin (180) 
 Marcus (205) 
 Marianne (145) 
 Ronny (135) 
 Sepehr (150) 
 Postorder Traversal: 
 Adam (185) 
 Andy (210) 
 Fareed (170) 
 Gloria (140) 
 Collin (150) 
 Chaz (145) 
 Aidan (160) 
 Kevin (180) 
 Katie (170) 
 Marianne (145) 
 Marcus (205) 
 Jeffrey (190) 
 Ronny (135) 
 Henry (135) 
 Sepehr (150) 
 Height: 7 
 Number of leaves: 5 
 Enter a name to search for: Ronny 
 Name: Ronny, Weight: 135 
 Minimum weight: 135 
 First name in alphabetical order: Adam
 */