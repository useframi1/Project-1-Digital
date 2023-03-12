#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

set<char> validChars;

bool isValid(string input, set<char> validChars)
{
    int i = 0;
    bool valid = false;
    while (i < input.length() && ((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122) || validChars.find(input[i]) != validChars.end()))
    {
        i++;
    }
    if (i == input.length())
        valid = true;
    return valid;
}

//still not finished
vector<int> getMinterms(string input,set<char> variables)
{
    string minterm = "";
    vector<int> minterms;
    int bitValue;
    for (int i = 0; i < input.length(); i++)
    {
        while (i<input.length() && input[i] != '+' && input[i] != ' ')
        {
            minterm+=input[i];
            i++;
        }
        while (i<input.length() && (input[i] == '+' || input[i] == ' '))
        {
            i++;
        }
        
        minterms.push_back(0);
        for (int j = 0; j < minterm.length(); j++)
        {
            if (j+1<minterm.length() && minterm[j+1] == 39)
            {
                bitValue = 0;
            }
            else if (j+1<minterm.length() && minterm[j+1] != 39)
            {
                bitValue = 1;
            }
            minterms[minterms.size()-1] += bitValue*pow(2,variables.size()-j-1);
        }
        minterm = "";
    }
 
    return minterms;
}

set<char> getVariables(string input)
{
    set<char> variables;
    for (int i = 0; i < input.length(); i++)
    {
        if (validChars.find(input[i]) == validChars.end())
        {
            variables.insert(input[i]);
        }
    }
    
    return variables;
}

void printTruthTable(vector<int> minterms, set<char> variables)
{
    int truthValue = 0;
    vector<vector<int> > truthTableCombs(pow(2,variables.size()),vector<int>(variables.size()));
    for (int i = 0; i < variables.size(); i++)
    {
        truthValue = 0;
        int x = 0;
        for (int j = 0; j < pow(2,variables.size()); j++)
        {
            if (x == pow(2,variables.size()-i-1))
            {
                truthValue = (truthValue == 0) ? 1:0;
                x = 0;
            }
            truthTableCombs[j][i] = truthValue;
            x++;
        }
    }

    vector<int> output(pow(2,variables.size()));
    for (int i = 0; i < minterms.size(); i++)
    {
        output[minterms[i]] = 1;
    }
    

    for (int i = 0; i < pow(2,variables.size()); i++)
    {
        for (int j = 0; j < variables.size(); j++)
        {
            cout<<truthTableCombs[i][j]<<" ";            
        }
        cout<<output[i]<<endl;
    }

    
}

int main()
{
    validChars.insert(39);
    validChars.insert(' ');
    validChars.insert('+');
    validChars.insert('&');
    validChars.insert('!');
    string input = "abc'";

    if (isValid(input, validChars))
    {
        cout << "valid" << endl;
    }
    else
        cout << "invalid" << endl;

    set<char> variables = getVariables(input);
    vector<int> minterms = getMinterms(input, variables);
    printTruthTable(minterms, variables);

    for (int i = 0; i < minterms.size(); i++)
    {
        cout << minterms[i] << endl;
    }

    set<char>::iterator iter;
    for (iter = variables.begin(); iter != variables.end(); iter++)
    {
        cout << *iter << endl;
    }
}