#include <bits/stdc++.h>
using namespace std;

vector<int> readString(string input) {
    stringstream s(input);
    int a;
    vector<int> v;
    while (s >> a) {
        v.push_back(a);
    }
    return v;
}

vector<vector<int>> readMooreString(string input) {
    stringstream s(input);
    int a;
    vector<vector<int>> ret;
    vector<int> m;
    vector<int> o;
    while (!s.eof()) {
        s >> a;
        m.push_back(a);
        s >> a;
        m.push_back(a);
        s >> a;
        o.push_back(a);
    }
    ret.push_back(m);
    ret.push_back(o);
    return ret;
}

string getMooreOutput(vector<int> initialStates, vector<vector<int>> moore, vector<int> output, string input) {
    int currentState = initialStates[0];
    string outputWord = "";
    for (int i = 0; i < input.size(); i++) {
        currentState = moore[currentState][input[i] - '0'];
        if (currentState == -1) {
            return outputWord;
        }
        outputWord += output[currentState] + 'A';
    }
    return outputWord;
}

int main() {
    vector<int> initialStates;
    vector<vector<int>> moore;
    vector<int> output;
    string word;
    fstream f;
    f.open("./moore.txt", ios::in);
    if (!f) {
        cout << strerror(errno);
        exit(0);
    }
    getline(f, word);
    initialStates = readString(word);
    while (getline(f, word)) {
        vector<vector<int>> r = readMooreString(word);
        moore.push_back(r[0]);
        output.push_back(r[1][0]);
    }
    f.close();
    cout << "Machine loaded successfully\nEnter the string: ";
    cin >> word;
    cout << "The output for the given string is: " << getMooreOutput(initialStates, moore, output, word);
}