#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

array<bitset<100>, 100> GenerateGraph() {

    array<bitset<100>, 100> res;
    for (auto& row : res)
        row.reset();
    
    string line = "     ";
    while (getline(fin, line) && line.size()) {
        const int n1 = atoi(&line[0]);
        const int n2 = atoi(&line[3]);

        res[n1][n2] = true;
    }

    return res;
}


vector<vector<int>> ParseUpdates() {

    vector<vector<int>> res;

    string update;
    while (getline(fin, update)) {
        vector<int> curr;
        
        stringstream ss(update);
        string page;

        while (getline(ss, page, ',')) {
            curr.push_back(stoi(page));
        }

        res.push_back(curr);        
    }
    
    return res;
}


unsigned long long solve(array<bitset<100>, 100>& graph, vector<vector<int>> vec) {

    unsigned long long res = 0;

    const int size = vec.size();
    for (int i = 0; i < size; i++) {

        bool correctOrder = true;
        
        const int n = vec[i].size();
        for (int j = 0; j < n && correctOrder; j++) {
            for (int k = 0; k < j && correctOrder; k++) {
                const int curr = vec[i][j];
                const int prev = vec[i][k];

                if (graph[curr][prev] == true) {
                    correctOrder = false;
                }
            }
        }

        if (correctOrder) {
            res += vec[i][n / 2];
        }
    }

    return res;
}

int main(void) {

    string line;

    array<bitset<100>, 100> graph = GenerateGraph();
    vector<vector<int>> updatesVec = ParseUpdates();

    unsigned long long res = solve(graph, updatesVec);
    cout << res << '\n';

    cout << endl;
    return 0;
}