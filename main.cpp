#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;


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

map<int, int> getMintermsMap(string minterm, set<char> variables, int &numOfBars)
{
    map<int, int> mintermsMap;
    for (int j = 0; j < minterm.length(); j++)
    {
        int index = 0;
        int x = 0;
        for(char item:variables)
        {
            if(item == minterm[j]) break;
            index++;
        }
        if(j+1<minterm.length() && minterm[j+1] == 39)
        {
            numOfBars++;
            x = pow(2,variables.size()-index-1);
        }
        
        for (int k = 0; k < pow(2,variables.size()); k++)
        {
            if (x != pow(2,variables.size()-index-1))
            {
                x++;
            }
            else 
            {
                mintermsMap.insert(pair<int,int>(k,0));
                for (int p = 0; p < x; p++)
                {
                    mintermsMap[k]++;
                    k++;
                }
                k--;
                x = 0;
            }
        }
    }
    return mintermsMap;
}

set<int> getMinterms(string input,set<char> variables)
{
    string minterm = "";
    set<int> minterms;
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
        i--;
        int numOfBars = 0;
        map<int, int> mintermsMap = getMintermsMap(minterm, variables, numOfBars);
        for (pair<int, int> item:mintermsMap)
        {
            if(item.second == minterm.length()-numOfBars)
                minterms.insert(item.first);
        }
        minterm = "";
    }

    return minterms;
}

set<char> getVariables(string input, set<char> validChars)
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

void printTruthTable(set<int> minterms, set<char> variables)
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
    set<int>::iterator iter;
    for (iter = minterms.begin();iter!=minterms.end();iter++)
    {
        output[*iter] = 1;
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
    set<char> validChars;

    validChars.insert(39);
    validChars.insert(' ');
    validChars.insert('+');
    validChars.insert('&');
    validChars.insert('!');
    string input = "ac + ac'b'";

    if (isValid(input, validChars))
    {
        cout << "valid" << endl;
        set<char> variables = getVariables(input, validChars);
        set<int> minterms = getMinterms(input, variables);
        printTruthTable(minterms, variables);
    }
    else
        cout << "invalid" << endl;

}