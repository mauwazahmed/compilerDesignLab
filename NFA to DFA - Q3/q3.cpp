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

void generateDFA(FA nfa, map<string, vector<string>> closures) {
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
    dfa.displayTransitionTable();
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
void runner() {
    FA nfa;
    vector<int> initialStates;
    vector<int> finalStates;
    int lines = 0;
    int symbols = 0;
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
        vector<vector<int>> r = readCSString(word);
        nfa.states.push_back(to_string(lines));
        if (lines == 0) {
            for (int i = 0; i < r.size(); i++) {
                nfa.symbols.push_back(to_string(i));
            }
        }
        for (int i = 0; i < r.size(); i++) {
            for (int j = 0; j < r[i].size(); j++) {
                if (r[i][j] != -1) {
                    nfa.transition[{to_string(lines), to_string(i)}].push_back(to_string(r[i][j]));
                }
            }
        }
        lines++;
    }
    map<string, vector<string>> closures = generateClosures(nfa);
    generateDFA(nfa, closures);
}

int main() {
    runner();
    return 0;
}