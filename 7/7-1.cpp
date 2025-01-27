#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

bool dfs(ull curr, ull target, vector<ull>& vec, ull idx) {

    if (idx >= vec.size())
        return curr == target;

    return dfs(curr * vec[idx], target, vec, idx + 1) ||
           dfs(curr + vec[idx], target, vec, idx + 1);
}

ull solve(ull lhs, vector<ull>& rhs) {

    ull res = 0;
    if (dfs(rhs[0], lhs, rhs, 1))
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