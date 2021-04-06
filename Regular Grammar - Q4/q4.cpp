#include <bits/stdc++.h>
using namespace std;

string to_string(vector<string> a) {
    string ans;
    for (auto i : a) {
        ans += i + ",";
    }
    ans.pop_back();
    return ans;
}

string to_string(set<string> a) {
    string ans;
    for (auto i : a) {
        ans += i + ",";
    }
    ans.pop_back();

    return ans;
}

vector<vector<int>> readCSString(string input) {
    stringstream s(input);
    string a;
    vector<vector<int>> v;
    while (s >> a) {
        istringstream f(a);
        string n;
        vector<int> _v;
        while (getline(f, n, ',')) {
            _v.push_back(stoi(n));
        }
        v.push_back(_v);
    }
    return v;
}

vector<int> readString(string input) {
    stringstream s(input);
    int a;
    vector<int> v;
    while (s >> a) {
        v.push_back(a);
    }
    return v;
}

vector<string> readGrammarString(string input) {
    stringstream s(input);
    vector<string> v;
    string a;
    while (s >> a) {
        v.push_back(a);
    }
    return v;
}

bool checkFinal(string input) {
    stringstream s(input);
    string a;
    while (getline(s, a, ',')) {
        if (a == "fin") {
            return true;
        }
    }
    return false;
}

class FA {
   public:
    vector<string> states;
    vector<string> symbols;
    map<pair<string, string>, vector<string>> transition;

    void displayTransitionTable() {
        cout << "-----------------TRANSITION TABLE-----------------\n";
        cout << "STATE\t"
             << "SYMBOL\t"
             << " STATE\n";
        for (auto i : transition) {
            for (auto j : i.second)
                cout << i.first.first + "\t" + i.first.second + "\t  " + j << "\n";
        }
    }
};

vector<string> calcClosure(FA nfa, string state) {
    vector<string> ans;
    ans.push_back(state);
    if (nfa.transition[{state, "eps"}].size() == 0) return ans;

    for (auto j : nfa.transition[{state, "eps"}]) {
        // ans.push_back(j);
        vector<string> aans = calcClosure(nfa, j);
        for (auto k : aans) {
            ans.push_back(k);
        }
    }
    return ans;
}

map<string, vector<string>> generateClosures(FA nfa) {
    map<string, vector<string>> ans;

    for (auto i : nfa.states) {
        ans[i] = calcClosure(nfa, i);
    }
    return ans;
}

FA NFAtoDFA(FA nfa, map<string, vector<string>> closures) {
    FA dfa;
    set<set<string>> isChecked;
    queue<set<string>> q;
    set<string> first;
    for (auto i : closures[nfa.states[0]]) first.insert(i);
    isChecked.insert(first);

    q.push(first);
    while (!q.empty()) {
        set<string> sstates = q.front();
        q.pop();
        dfa.states.push_back(to_string(sstates));
        for (auto sym : nfa.symbols) {
            set<string> dest;
            for (auto state : sstates) {
                for (auto k : nfa.transition[{state, sym}]) {
                    dest.insert(k);
                    for (auto l : closures[k]) dest.insert(l);
                }
            }
            if (!dest.empty()) {
                dfa.transition[{to_string(sstates), sym}].push_back(to_string(dest));
                if (isChecked.find(dest) == isChecked.end()) {
                    isChecked.insert(dest);
                    q.push(dest);
                }
            }
        }
    }
    return dfa;
}

FA generateDFA() {
    FA nfa;
    fstream f;
    string word;
    f.open("./input.txt", ios::in);
    if (!f) {
        cout << strerror(errno);
        exit(0);
    }
    vector<vector<string>> grammar;
    while (getline(f, word)) {
        grammar.push_back(readGrammarString(word));
    }
    for (int i = 0; i < grammar.size(); i++) {
        for (int j = 0; j < grammar[i].size(); j++) {
            string state = grammar[i][0];
            if (j == 0) {
                nfa.states.push_back(grammar[i][0]);
                continue;
            }
            if (grammar[i][j].size() == 1) {
                if (find(nfa.symbols.begin(), nfa.symbols.end(), grammar[i][j]) == nfa.symbols.end()) {
                    nfa.symbols.push_back(grammar[i][j]);
                }
                nfa.transition[{state, grammar[i][j]}].push_back("fin");
            } else {
                nfa.transition[{state, grammar[i][j].at(0) + (string) ""}].push_back(grammar[i][j][1] + (string) "");
            }
        }
    }
    map<string, vector<string>> closures = generateClosures(nfa);
    return NFAtoDFA(nfa, closures);
}

void checkString(FA dfa, string input) {
    string currentState = "S";
    for (int i = 0; i < input.size(); i++) {
        if (dfa.transition.find({currentState, input[i] + (string) ""}) == dfa.transition.end()) {
            break;
        }
        currentState = dfa.transition[{currentState, input[i] + (string) ""}][0];
        if (checkFinal(currentState)) {
            break;
        }
    }
    if (checkFinal(currentState)) {
        cout << "String accepted";
    } else {
        cout << "String not accepted";
    }
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    FA dfa = generateDFA();
    checkString(dfa, input);
    return 0;
}