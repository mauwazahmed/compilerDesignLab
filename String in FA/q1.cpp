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

bool checkString(vector<int> initialStates, vector<int> finalStates, vector<vector<int>> DFA, string input) {
    int currentState;
    currentState = initialStates[0];
    for (int i = 0; i < input.size(); i++) {
        currentState = DFA[currentState][input[i] - '0'];
        if (currentState == -1) {
            return false;
        }
    }
    return (find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end());
}

int main() {
    vector<int> initialStates, finalStates;
    vector<vector<int>> DFA;
    string word;
    fstream f;
    f.open("./input.txt", ios::in);
    if (!f) {
        cout << strerror(errno);
        exit(0);
    }
    getline(f, word);
    initialStates = readString(word);
    getline(f, word);
    finalStates = readString(word);
    while (getline(f, word)) {
        DFA.push_back(readString(word));
    }
    f.close();
    cout << "DFA loaded successfully\nEnter the string: ";
    cin >> word;
    checkString(initialStates, finalStates, DFA, word) ? cout << "Accepted" : cout << "Not accepted";

}