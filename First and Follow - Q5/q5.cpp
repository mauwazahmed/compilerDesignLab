#include <bits/stdc++.h>
using namespace std;
set<char> ss;
void entry(int, int);
string production[25];
string variable;
int limit;
int c = 0;
int p = 0;
string first[25];
string follow[25];
int fst, flw;
string terminal;

void find_first(char ch)
{
    int i;
    char c;

    for (i = 0; i < limit; i++)
    {
        if (ch == production[i][0] && ch != production[i][2])
        {
            if (isupper(production[i][2]))
            {
                find_first(production[i][2]);
            }
            if (terminal.find(production[i][2]) < terminal.length())
            {
                first[fst] += production[i][2];
            }
            if (production[i][2] == 'p')
                p = 1;
        }
    }
    return;
}

void find_follow(char ch)
{
    int i, j, l;
    for (i = 0; i < limit; i++)
    {
        l = production[i].length();
        for (j = 2; j < l; j++)
        {
            if (ch == production[i][j])
            {
                if (islower(production[i][j + 1]))
                {
                    if (follow[flw].find(production[i][j + 1]) > follow[flw].length())
                        follow[flw] += production[i][j + 1];
                    c++;
                }
                if (j < l - 1)
                {
                    for (int k = 0; k < variable.length(); k++)
                    {
                        if (production[i][j + 1] == variable[k])
                        {
                            follow[flw] += first[k];
                            follow[flw].erase(follow[flw].begin() + follow[flw].find('p'));
                        }
                    }
                    c++;
                }
                if (j == l - 1 && production[i][0] != production[i][j])
                {
                    c = 0;
                    find_follow(production[i][0]);
                }
            }
        }
    }
    if (c == 0)
        follow[flw] += "$";
    return;
}


int main() {
    int l, j = 0, i, k;
    char ch;
    ifstream obj("input.txt");
    string line;
    while (!obj.eof())
    {
        getline(obj, production[j]);
        l = production[j].length();
        for (i = 0; i < l; i++)
        {
            ch = production[j][i];
            if (isupper(ch) && variable.find(ch) > variable.length())
                variable += ch;
            if (!isupper(ch) && terminal.find(ch) > terminal.length() && ch != 'p' && ch != ' ')
            {
                terminal += production[j][i];
            }
        }
        j++;
    }
    sort(terminal.begin(), terminal.end());
    terminal += '$';
    cout << "terminals are = ";
    for (int i = 0; i < terminal.length(); i++)
    {
        cout << terminal[i] << " ";
    }
    cout << endl;
    cout << endl;
    limit = j;
    obj.close();
    j = 0;
    fst = 0;
    for (k = 0; k < variable.length(); k++)
    {
        cout << "first of " << variable[j] << " is { ";
        find_first(variable[j]);
        if (p == 1)
            first[fst] += 'p';
        cout << first[fst] << " }\n";
        fst++;
        j++;
    }
    cout << endl;
    flw = 0;
    for (k = 0; k < variable.length(); k++)
    {
        c = 0;
        cout << "follow of " << variable[k] << " is { ";
        find_follow(variable[k]);
        cout << follow[flw] << " }\n";
        flw++;
    }
    cout << "\n\t";
}


