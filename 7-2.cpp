#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

bool dfs(ull curr, ull target, vector<ull>& vec, ull idx) {

    if (idx >= vec.size())
        return curr == target;

    ull concatNum = stoull(to_string(curr) + to_string(vec[idx]));

    return dfs(curr * vec[idx], target, vec, idx + 1) ||
           dfs(curr + vec[idx], target, vec, idx + 1) ||
           dfs(concatNum,       target, vec, idx + 1);
}

ull solve(ull lhs, vector<ull>& vec) {

    ull res = 0;
    if (dfs(vec[0], lhs, vec, 1))
        return lhs;
    
    return 0;
}

int main(void) {

    string line;

    ull res = 0;
    while (getline(fin, line)) {
        stringstream ss(line);
        
        ull lhs;
        ss >> lhs;

        ss >> line;

        vector<ull> vec;
        ull rhs;
        while (ss >> rhs) {
            vec.push_back(rhs);
        }

        res += solve(lhs, vec);
    }

    cout << res;
    cout << endl;
    return 0;
}