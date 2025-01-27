#include <bits/stdc++.h>

using namespace std;

bool IsSafeLevel(const vector<int>& vec) {

    if (vec.size() < 2)
        return true;

    auto it = adjacent_find(vec.begin(), vec.end(), [](int a, int b) {
        return (a == b) || abs(a - b) > 3;
    });

    if (it != vec.end()) {
        return false;
    }

    if (is_sorted(vec.begin(), vec.end()) || is_sorted(vec.rbegin(), vec.rend())) {
        return true;
    }

    return false;
}

int solve(vector<int>& arr) {

    if (IsSafeLevel(arr))
        return true;

    // Bruteforce this shit
    for (int i = 0; i < arr.size(); i++) {
        vector<int> copy = arr;
        copy.erase(copy.begin() + i);
        if (IsSafeLevel(copy))
            return true;
    }

    return false;
}

int main(void) {

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int res = 0;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<int> levels;
        int n;
        while (ss >> n) {
            levels.push_back(n);
        }

        bool safe = solve(levels);
        res += safe;
        fout << (safe ? "safe" : "unsafe") << '\n';
    }

    cout << res;
    cout << endl;
    return 0;
}