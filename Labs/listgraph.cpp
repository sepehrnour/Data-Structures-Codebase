#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    Node(string label, int weight)
    {
        this->label = label;
        this->weight = weight;
        next = nullptr;
    }

    string getLabel() const
    {
        return label;
    }

    int getWeight() const
    {
        return weight;
    }

    Node *getNext() const
    {
        return next;
    }

    void setNext(Node *next)
    {
        this->next = next;
    }

private:
    string label;
    int weight;
    Node *next;
};

class Graph
{
public:
    int numVertices;
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjacencyList = new Node *[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            adjacencyList[i] = nullptr;
        }
    }

    ~Graph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            Node *node = adjacencyList[i];
            while (node != nullptr)
            {
                Node *temp = node;
                node = node->getNext();
                delete temp;
            }
        }
        delete[] adjacencyList;
    }

    void setVertexLabels()
    {
        for (int i = 0; i < numVertices; i++)
        {
            string label;
            cout << "Enter label for vertex " << i << ": ";
            getline(cin, label, '\n');
            vertexLabels.push_back(label);
        }
    }

    void addEdge(int startIndex, int endIndex, int weight)
    {
        Node *newNode = new Node(vertexLabels[endIndex], weight);
        newNode->setNext(nullptr); // Set the next pointer to nullptr
        if (adjacencyList[startIndex] == nullptr)
        {
            adjacencyList[startIndex] = newNode;
        }
        else
        {
            Node *currentNode = adjacencyList[startIndex];
            while (currentNode->getNext() != nullptr)
            {
                currentNode = currentNode->getNext();
            }
            currentNode->setNext(newNode);
        }
    }

    void printEdges() const
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Edges for vertex " << vertexLabels[i] << ":" << endl;
            if (adjacencyList[i] == nullptr)
            {
                cout << "  No edges" << endl;
            }
            else
            {
                Node *node = adjacencyList[i];
                while (node != nullptr)
                {
                    cout << "  " << node->getLabel() << " (" << node->getWeight() << ")" << endl;
                    node = node->getNext();
                }
            }
        }
    }

private:
    Node **adjacencyList;
    vector<string> vertexLabels;
};

int main()
{
    int numVertices;
    cout << "How many vertices are there? ";
    cin >> numVertices;

    Graph graph(numVertices);

    cin.ignore(); // ignore newline character after reading numVertices

    graph.setVertexLabels();

    for (int i = 0; i < numVertices; i++)
    {
        int startIndex, endIndex, weight;
        cout << "Enter start vertex index (-1 to quit): ";
        cin >> startIndex;
        if (startIndex == -1)
        {
            break;
        }
        if (startIndex >= numVertices || startIndex < 0)
        {
            cout << "Invalid start vertex index. Please enter an index between 0 and " << numVertices - 1 << "." << endl;
            continue;
        }
        cout << "Enter end vertex index: ";
        cin >> endIndex;
        if (endIndex >= numVertices || endIndex < 0)
        {
            cout << "Invalid end vertex index. Please enter an index between 0 and " << numVertices - 1 << "." << endl;
            continue;
        }
        cout << "Enter weight: ";
        cin >> weight;
        graph.addEdge(startIndex, endIndex, weight);
    }

    graph.printEdges();

    return 0;
}