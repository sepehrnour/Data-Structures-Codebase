#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>
#include <cmath>
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

class Block
{
private:
    HashTable privateVariables;

public:
    void insertPrivateVariable(const string &variable, int value)
    {
        privateVariables.insert(variable, value);
    }

    int searchPrivateVariable(const string &variable)
    {
        return privateVariables.search(variable);
    }

    void clearPrivateVariables()
    {
        privateVariables.clear();
    }
};

class Interpreter
{
private:
    HashTable globalVariables;
    stack<Block> blocks;

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
        string previousToken = "";
        while (getline(iss, token, ' '))
        {
            // Process each token here
            // Read the first token from the line

            if (token == "COM" || line.empty())
            {
                return; // Ignore the rest of the line
            }
            else if (token == "START")
            {
                blocks.push(Block());
            }
            else if (token == "FINISH")
            {
                if (!blocks.empty())
                {
                    blocks.top().clearPrivateVariables();
                    blocks.pop();
                }
                else
                {
                    cout << "Error: Unmatched FINISH at line number " << lineNumber << endl;
                }
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
                        if (!blocks.empty())
                        {
                            blocks.top().insertPrivateVariable(variable, value);
                        }
                        else
                        {
                            globalVariables.insert(variable, value);
                        }
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
                variable = token;

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
            }
        }
        previousToken = token;
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
        string previousToken = "";
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
                if (isOperator(token))
                {
                    string nextToken;
                    if (iss >> nextToken)
                    {
                        int operand;
                        if (isNumber(nextToken))
                        {
                            operand = stoi(nextToken);
                        }
                        else
                        {
                            operand = findVariableValue(nextToken);
                            if (operand == -1)
                            {
                                return -1; // Unknown variable in expression
                            }
                        }

                        if (token == "+")
                        {
                            result += operand;
                        }
                        else if (token == "-")
                        {
                            result -= operand;
                        }
                        else if (token == "*")
                        {
                            result *= operand;
                        }
                        else if (token == "/")
                        {
                            if (operand != 0)
                            {
                                result /= operand;
                            }
                            else
                            {
                                cout << "Division by zero at line number " << lineNumber << endl;
                                return -1;
                            }
                        }
                        else if (token == "%")
                        {
                            if (operand != 0)
                            {
                                result %= operand;
                            }
                            else
                            {
                                cout << "Modulo by zero at line number " << lineNumber << endl;
                                return -1;
                            }
                        }
                        else if (token == "^")
                        {
                            result = pow(result, operand);
                        }
                        else if (token == "++")
                        {
                            string variable = previousToken;
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
                    }
                    else
                    {
                        cout << "Invalid expression at line number " << lineNumber << endl;
                        return -1;
                    }
                }
                else
                {
                    cout << "Invalid operator at line number " << lineNumber << endl;
                    return -1;
                }
            }
        }
        previousToken = token;
        return result;
    }

    int findVariableValue(const string &variable)
    {
        if (!blocks.empty())
        {
            int value = blocks.top().searchPrivateVariable(variable);
            if (value != -1)
            {
                return value;
            }
        }
        return globalVariables.search(variable);
    }

    void updateVariableValue(const string &variable, int value)
    {
        if (!blocks.empty())
        {
            blocks.top().insertPrivateVariable(variable, value);
        }
        else
        {
            globalVariables.insert(variable, value);
        }
    }
};

int main()
{
    Interpreter interpreter;
    interpreter.processProgram("program.borg");

    return 0;
}

/*
Sample Borg program provided by Professor
COM HERE IS OUR FIRST BORG PROGRAM

COM WHAT A ROBUST LANGUAGE IT IS

START

VAR BORAMIR = 25
VAR LEGOLAS = 101

PRINT BORAMIR
BORAMIR ++
PRINT LEGOLAS
PRINT GANDALF
PRINT BORAMIR * 2

COM

COM NESTED BLOCK

COM

START
VAR GANDALF = 49
PRINT GANDALF
PRINT BORAMIR
FINISH

PRINT GANDALF

START
LEGOLAS = 1000
PRINT LEGOLAS
FINISH

PRINT LEGOLAS
LEGOLAS --
PRINT LEGOLAS

FINISH

My codes output on sample code from Prof
BORAMIR IS 25
Unknown variable ++ at line number 11
LEGOLAS IS 101
Unknown variable in expression at line number 13
BORAMIR * 2 IS 50
GANDALF IS 49
Unknown variable in expression at line number 25
Unknown variable in expression at line number 28
Unknown variable in expression at line number 32
LEGOLAS IS 101
Unknown variable  at line number 36
LEGOLAS IS 101

My custom Borg program
COM IM TRYING MY BEST

COM I"VE BEEN STUCK ON MAKING ++ AND -- WORK IN THE RIGHT ORDER
COM BUT THEY JUST WONT
COM I BUILT AN ENTIRE VARIABLE MANAGEMENT SYSTEM FOR THE INTERPRETER
COM DID NOT HAVE TIME TO GET IT RUNNING PROPERLY 

START

VAR SADNESS = 100
VAR STRESS = 1000

PRINT SADNESS
PRINT STRESS * 100

COM I HOPE YOU CAN HAVE MERCY ON ME

FINISH

START
PRINT CAIN
VAR ABEL = 2
PRINT ABEL
PRINT ABEL * 345

FINISH

The ouput for my custom Borg program
SADNESS IS 100
STRESS * 100 IS 100000
Unknown variable in expression at line number 21
ABEL IS 2
ABEL * 345 IS 690
*/