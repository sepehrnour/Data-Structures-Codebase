#include <iostream>
using namespace std;

class HashTable {
    private:
        static const int TABLE_SIZE = 27;
        int table[TABLE_SIZE];
        
        int Hash(int value);
        
    public:
        HashTable();
        int add(int value);
        int find(int value);
};

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = -1;
    }
}

int HashTable::Hash(int value) {
    return value % TABLE_SIZE;
}

int HashTable::add(int value) {
    int index = Hash(value);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = (index + i) % TABLE_SIZE;
        
        if (table[j] == -1) {
            table[j] = value;
            return j;
        }
    }
    
    return -1;
}

int HashTable::find(int value) {
    int index = Hash(value);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        int j = (index + i) % TABLE_SIZE;
        
        if (table[j] == value) {
            return j;
        }
        
        if (table[j] == -1) {
            return -1;
        }
    }
    
    return -1;
}

int main() {
    HashTable table;
    char choice = ' ';
    
    while (choice != 'Q' && choice != 'q') {
        cout << "Enter A to add a value, F to find a value, or Q to quit: ";
        cin >> choice;
        
        switch (choice) {
            case 'A':
            case 'a': {
                int value;
                cout << "Enter a value to add: ";
                cin >> value;
                
                int result = table.add(value);
                
                if (result == -1) {
                    cout << "Table is full." << endl;
                } else {
                    cout << "Added value " << value << " at index " << result << "." << endl;
                }
                break;
            }
            case 'F':
            case 'f': {
                int value;
                cout << "Enter a value to find: ";
                cin >> value;
                
                int result = table.find(value);
                
                if (result == -1) {
                    cout << "Value " << value << " not found." << endl;
                } else {
                    cout << "Value " << value << " found at index " << result << "." << endl;
                }
                break;
            }
            case 'Q':
            case 'q':
                cout << "Exiting program." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    
    return 0;
}