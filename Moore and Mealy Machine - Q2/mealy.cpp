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

vector<vector<int>> readMealyString(string input) {
    stringstream s(input);
    int a;
    vector<vector<int>> ret;
    vector<int> m;
    vector<int> o;
    while (!s.eof()) {
        s >> a;
        m.push_back(a);
        s >> a;
        o.push_back(a);
    }
    ret.push_back(m);
    ret.push_back(o);
    return ret;
}

string getMealyOutput(vector<int> initialStates, vector<vector<int>> mealy, vector<vector<int>> output, string input) {
    int currentState = initialStates[0], prevState;
    string outputWord = "";
    for (int i = 0; i < input.size(); i++) {
        prevState = currentState;
        currentState = mealy[currentState][input[i] - '0'];
        if (currentState == -1) {
            return outputWord;
        }
        outputWord += output[prevState][input[i] - '0'] + 'A';
    }
    return outputWord;
}

int main() {
    vector<int> initialStates;
    vector<vector<int>> mealy;
    vector<vector<int>> output;
    string word;
    fstream f;
    f.open("./mealy.txt", ios::in);
    if (!f) {
        cout << strerror(errno);
        exit(0);
    }
    getline(f, word);
    initialStates = readString(word);
    while (getline(f, word)) {
        vector<vector<int>> r = readMealyString(word);
        mealy.push_back(r[0]);
        output.push_back(r[1]);
    }
    f.close();
    cout << "Machine loaded successfully\nEnter the string: ";
    cin >> word;
    cout << "The output for the given string is: " << getMealyOutput(initialStates, mealy, output, word);
}