#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>
#include <unordered_map>
using namespace std;

const int TABLESIZE = 100;

class Node
{
public:
    string variable;
    int value;
    Node *next;

    Node(const string &var, int val) : variable(var), value(val), next(nullptr) {}
};

class HashTable
{
private:
    vector<Node *> table;

public:
    HashTable()
    {
        table.resize(TABLESIZE, nullptr);
    }

    ~HashTable()
    {
        clear();
    }

    void insert(const string &variable, int value)
    {
        int index = hashFunction(variable);
        Node *newNode = new Node(variable, value);

        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else
        {
            Node *curr = table[index];
            while (curr->next != nullptr)
            {
                if (curr->variable == variable)
                {
                    curr->value = value;
                    delete newNode;
                    return;
                }
                curr = curr->next;
            }
            if (curr->variable == variable)
            {
                curr->value = value;
                delete newNode;
                return;
            }
            curr->next = newNode;
        }
    }

    int search(const string &variable)
    {
        int index = hashFunction(variable);

        if (table[index] != nullptr)
        {
            Node *curr = table[index];
            while (curr != nullptr)
            {
                if (curr->variable == variable)
                {
                    return curr->value;
                }
                curr = curr->next;
            }
        }

        return -1; // Variable not found
    }

    void clear()
    {
        for (Node *node : table)
        {
            while (node != nullptr)
            {
                Node *temp = node;
                node = node->next;
                delete temp;
            }
        }
        table.clear();
    }

private:
    int hashFunction(const string &variable)
    {
        int sum = 0;
        for (size_t i = 0; i < variable.length(); ++i)
        {
            sum += variable[i] * (i + 1);
        }
        return sum % TABLESIZE;
    }
};

class Interpreter
{
private:
    HashTable hashTable;
    vector<HashTable> scopes;

public:
    void processProgram(const string &filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        int lineNumber = 1;

        while (getline(inputFile, line))
        {
            processLine(line, lineNumber);
            lineNumber++;
        }

        inputFile.close();
    }

private:
    void processLine(const string &line, int lineNumber)
    {
        istringstream iss(line);
        string token;

        // Read the first token from the line
        iss >> token;

        if (token == "COM" || line.empty())
        {
            return; // Ignore the rest of the line
        }
        else if (token == "START")
        {
            scopes.push_back(HashTable());
        }
        else if (token == "FINISH")
        {
            if (!scopes.empty())
            {
                scopes.pop_back();
            }
            else
            {
                cout << "Error: Unmatched FINISH at line number " << lineNumber << endl;
            }
            hashTable.clear();
        }
        else if (token == "VAR")
        {
            string variable;
            string assignOp;
            string expression;

            // Read the variable, assignment operator, and expression from the line
            iss >> variable >> assignOp;
            getline(iss, expression);

            if (assignOp == "=")
            {
                int value = evaluateExpression(expression, lineNumber);
                if (value != -1)
                {
                    hashTable.insert(variable, value);
                }
                else
                {
                    cout << "Unknown variable in expression at line number " << lineNumber << endl;
                }
            }
            else
            {
                cout << "Invalid assignment operator at line number " << lineNumber << endl;
            }
        }
        else if (token == "PRINT")
        {
            string expression;
            getline(iss, expression);

            int value = evaluateExpression(expression, lineNumber);
            if (value != -1)
            {
                cout << expression << " IS " << value << endl;
            }
            else
            {
                cout << "Unknown variable in expression at line number " << lineNumber << endl;
            }
        }
        else if (token == "++")
        {
            string variable;
            iss >> variable;

            int value = findVariableValue(variable);
            if (value != -1)
            {
                updateVariableValue(variable, value + 1);
            }
            else
            {
                cout << "Unknown variable " << variable << " at line number " << lineNumber << endl;
            }
        }
        else if (token == "--")
        {
            string variable;
            iss >> variable;

            int value = findVariableValue(variable);
            if (value != -1)
            {
                updateVariableValue(variable, value - 1);
            }
            else
            {
                cout << "Unknown variable " << variable << " at line number " << lineNumber << endl;
            }
        }
        else
        {
            // Check if the token is an operator
            if (isOperator(token))
            {
                string expression;
                getline(iss, expression);

                int value = evaluateExpression(token + expression, lineNumber);
                if (value != -1)
                {
                    cout << token << expression << " IS " << value << endl;
                }
                else
                {
                    cout << "Unknown variable in expression at line number " << lineNumber << endl;
                }
            }
            else
            {
                cout << "Invalid command at line number " << lineNumber << endl;
            }
        }
    }

    bool isOperator(const string &token)
    {
        return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
    }

    bool isNumber(const string &str)
    {
        for (char c : str)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    int evaluateExpression(const string &expression, int lineNumber)
    {
        istringstream iss(expression);
        string token;
        int result = 0;
        bool isFirstToken = true;

        while (iss >> token)
        {
            if (isFirstToken)
            {
                if (isNumber(token))
                {
                    result = stoi(token);
                }
                else
                {
                    result = findVariableValue(token);
                    if (result == -1)
                    {
                        return -1;
                    }
                }
                isFirstToken = false;
            }
            else
            {
                if (token == "+")
                {
                    iss >> token;
                    if (isNumber(token))
                    {
                        result += stoi(token);
                    }
                    else
                    {
                        int value = findVariableValue(token);
                        if (value != -1)
                        {
                            result += value;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                }
                else if (token == "-")
                {
                    iss >> token;
                    if (isNumber(token))
                    {
                        result -= stoi(token);
                    }
                    else
                    {
                        int value = findVariableValue(token);
                        if (value != -1)
                        {
                            result -= value;
                        }
                        else
                        {
                            return -1;
                        }
                    }
                }
                else
                {
                    cout << "Invalid operator in expression at line number " << lineNumber << endl;
                    return -1;
                }
            }
        }

        return result;
    }

    int findVariableValue(const string &variable)
    {
        for (int i = scopes.size() - 1; i >= 0; --i)
        {
            int value = scopes[i].search(variable);
            if (value != -1)
            {
                return value;
            }
        }
        return hashTable.search(variable);
    }

    void updateVariableValue(const string &variable, int value)
    {
        for (int i = scopes.size() - 1; i >= 0; --i)
        {
            if (scopes[i].search(variable) != -1)
            {
                scopes[i].insert(variable, value);
                return;
            }
        }
        cout << "Unknown variable " << variable << endl;
    }
};

int main()
{
    Interpreter interpreter;
    interpreter.processProgram("program.borg"); // Replace with the filename of your BORG program
    return 0;
}