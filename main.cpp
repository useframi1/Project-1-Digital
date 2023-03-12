#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<string> getMinterms(string input)
{
    string minterm = "";
    vector<string> minterms;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '+' || input[i] == ' ')
        {
            if (minterm != "")
                minterms.push_back(minterm);
            minterm = "";
        }
        else
        {
            minterm += input[i];
        }
    }
    if (minterm != "")
        minterms.push_back(minterm);

    return minterms;
}

set<char> getVariables(vector<string> minterms)
{
    set<char> variables;
    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = 0; j < minterms[i].length(); j++)
        {
            if (minterms[i][j] != 39) // 39 = ascii value of apostrophe
            {
                variables.insert(minterms[i][j]);
            }
        }
    }
    return variables;
}

int main()
{
    string input = "abc' + dbc'+d'e' +";
    vector<string> minterms = getMinterms(input);
    set<char> variables = getVariables(minterms);

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