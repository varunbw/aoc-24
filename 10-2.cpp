#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

array<int, 5> dirs = {
    0, 1, 0, -1, 0
};

inline bool WithinBounds(const int i, const int j, const vector<vector<int>>& grid) {
    return i >= 0 && i < grid.size() &&
           j >= 0 && j < grid[0].size();
}


void dfs(const int i, const int j, const vector<vector<int>>& grid, int& score, vector<vector<bool>>& visited) {

    if (WithinBounds(i, j, grid) == false || visited[i][j])
        return;

    visited[i][j] = true;

    const int curr = grid[i][j];
    if (curr == 9) {
        visited[i][j] = false;
        score++;
        return;
    }

    for (int idx = 0; idx < 4; idx++) {
        const int iNew = i + dirs[idx];
        const int jNew = j + dirs[idx + 1];

        if (WithinBounds(iNew, jNew, grid) && grid[iNew][jNew] == grid[i][j] + 1)
            dfs(iNew, jNew, grid, score, visited);
    }

    visited[i][j] = false;
    return;
}


int solve(const vector<vector<int>>& grid) {

    const int m = grid.size();
    const int n = grid[0].size();

    int score = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            if (grid[i][j] == 0)
                dfs(i, j, grid, score, visited);
        }
    }

    return score;
}

int main(void) {

    string line;
    vector<vector<int>> vec;
    while (getline(fin, line)) {

        const int n = line.size();
        vector<int> row(n, 0);
        for (int i = 0; i < n; i++) {
            row[i] = line[i] - '0';
        }
        
        vec.push_back(row);
    }

    ull res = solve(vec);

    cout << res << '\n';
    cout << endl;
    return 0;
}