#include <iostream>
#include <string>

using namespace std;

class Graph {

public:
    int numPoints;
    string* labels;
    int** matrix;
    Graph(int n) {
        numPoints = n;
        labels = new string[n];
        matrix = new int*[n];
        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    ~Graph() {
        delete[] labels;
        for (int i = 0; i < numPoints; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void setLabels() {
        for (int i = 0; i < numPoints; i++) {
            cout << "Enter label for point " << i + 1 << ": ";
            cin >> labels[i];
        }
    }

    void addEdge(int from, int to) {
        matrix[from][to] = 1;
        matrix[to][from] = 1;
    }

    void listEdges() {
        cout << "List of edges:\n";
        for (int i = 0; i < numPoints; i++) {
            for (int j = i + 1; j < numPoints; j++) {
                if (matrix[i][j] == 1) {
                    cout << labels[i] << " -- " << labels[j] << endl;
                }
            }
        }
    }
};

int main() {
    int numPoints;
    cout << "Enter the number of points: ";
    cin >> numPoints;

    Graph graph(numPoints);
    graph.setLabels();

    char choice;
    do {
        string from, to;
        cout << "Enter names of two points to create an edge (separated by space): ";
        cin >> from >> to;
        int fromIndex = -1, toIndex = -1;
        for (int i = 0; i < graph.numPoints; i++) {
            if (graph.labels[i] == from) {
                fromIndex = i;
            }
            if (graph.labels[i] == to) {
                toIndex = i;
            }
            if (fromIndex != -1 && toIndex != -1) {
                break;
            }
        }
        if (fromIndex == -1 || toIndex == -1) {
            cout << "Invalid point names, please try again.\n";
        } else {
            graph.addEdge(fromIndex, toIndex);
            cout << "Edge created between " << from << " and " << to << endl;
        }
        cout << "Do you want to add another edge? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    graph.listEdges();

    return 0;
}
