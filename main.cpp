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
        set<char>::iterator iter;
        for(iter = variables.begin(); iter!=variables.end(); iter++)
        {
            if(*iter == minterm[j]) break;
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

        map<int, int>::iterator iter;
        for (iter = mintermsMap.begin(); iter!=mintermsMap.end(); iter++)
        {
            if((*iter).second == minterm.length()-numOfBars)
                minterms.insert((*iter).first);
        }
        minterm = "";
    }

    return minterms;
}

set<int> getMaxterms(set<int> minterms, set<char> variables)
{
    set<int> maxterms;

    for (int i = 0; i < pow(2, variables.size()); i++)
    {
        if(minterms.find(i) == minterms.end())
            maxterms.insert(i);
    }
    
    return maxterms;
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

vector<vector<int> > getTruthTableCombs(set<char> variables)
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

    return truthTableCombs;
}

vector<int> getOutput(set<int> minterms, set<char> variables)
{
    vector<int> output(pow(2,variables.size()));
    set<int>::iterator iter;
    for (iter = minterms.begin();iter!=minterms.end();iter++)
    {
        output[*iter] = 1;
    }

    return output;
}

void printTruthTable(vector<vector<int> > truthTableCombs, vector<int> output, set<char> variables)
{
    set<char>::iterator iter;
    for(iter = variables.begin();iter!=variables.end();iter++)
    {
        cout<<*iter<<"\t";
    }
    cout<<"|\tF"<<endl;
    for (int i = 0; i < 8*variables.size()+16; i++)
    {
        cout<<"-";
    }
    cout<<endl;
    for (int i = 0; i < pow(2,variables.size()); i++)
    {
        for (int j = 0; j < variables.size(); j++)
        {
            cout<<truthTableCombs[i][j]<<"\t";            
        }
        cout<<"|\t"<<output[i]<<endl;
    }    
}

void printCanonicalSOP(set<int> minterms, set<char> variables, vector<vector<int> > truthTableCombs)
{
    set<int>::iterator i;
    int temp = 0;
    for (i = minterms.begin(); i!= minterms.end(); i++)
    {
        set<char>::iterator iterVar = variables.begin();
        for (int j = 0; j < truthTableCombs[*i].size(); j++)
        {
            char var = *iterVar;
            iterVar++;

            if (truthTableCombs[*i][j] == 1)
                cout<<var;
            else 
                cout<<var<<"'";
        }
        if(temp<minterms.size()-1)
            cout<<" + ";
        temp++;
    }
    cout<<endl;
}

void printCanonicalPOS(set<int> maxterms, set<char> variables, vector<vector<int> > truthTableCombs)
{
    set<int>::iterator i;
    for (i = maxterms.begin(); i!= maxterms.end(); i++)
    {
        cout<<"(";
        set<char>::iterator iterVar = variables.begin();
        for (int j = 0; j < truthTableCombs[*i].size(); j++)
        {
            char var = *iterVar;
            iterVar++;

            if (truthTableCombs[*i][j] == 1)
                cout<<var<<"'";
            else 
                cout<<var;
            if(j<truthTableCombs[*i].size()-1)
                cout<<" + ";
        }
        cout<<")";
    }
    cout<<endl;
}

int main()
{
    set<char> validChars;

    validChars.insert(39);
    validChars.insert(' ');
    validChars.insert('+');
    string input = "a'a + b";

    if (isValid(input, validChars))
    {
        set<char> variables = getVariables(input, validChars);
        set<int> minterms = getMinterms(input, variables);
        set<int> maxterms = getMaxterms(minterms, variables);
        vector<vector<int> > truthTableCombs = getTruthTableCombs(variables);
        vector<int> output = getOutput(minterms, variables);

        cout<<"\nTruth Table:\n"<<endl;
        printTruthTable(truthTableCombs, output, variables);
        cout<<"\nCanonical SoP: ";
        printCanonicalSOP(minterms, variables, truthTableCombs);
        cout<<"\nCanonical PoS: ";
        printCanonicalPOS(maxterms, variables, truthTableCombs);
        cout<<endl;
    }
    else
        cout << "invalid" << endl;

}