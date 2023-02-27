#include <iostream>
#include <sstream>
using namespace std;

class IO 
{
public:
    void processSentence() 
    {
        string sentence;
        cout << "Sentence: ";
        getline(cin, sentence);

        stringstream ss(sentence);
        string word;
        while (getline(ss, word, ' ')) 
        {
            double value;
            if (istringstream(word) >> value) 
            {
                cout << value * 2 << endl;
            } 
            else 
            {
                cout << word << endl;
            }
        }
    }
};

int main() 
{
    IO IO;
    IO.processSentence();
    return 0;
}