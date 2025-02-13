#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long

ifstream fin("input.txt");
ofstream fout("output.txt");

array<int, 5> dirs = {0, 1, 0, -1, 0};

template <typename T>
bool WithinBounds(const int i, const int j, const vector<T>& vec) {
    return i >= 0 && i < vec.size() &&
           j >= 0 && j < vec[0].size();
}


void MarkID(int i, int j, vector<string>& grid, vector<vector<bool>>& visited, vector<vector<int>>& idGrid, int currId) {
    visited[i][j] = true;
    idGrid[i][j] = currId;

    for (int idx = 0; idx < 4; idx++) {
        int iNew = i + dirs[idx];
        int jNew = j + dirs[idx + 1];

        if (WithinBounds(iNew, jNew, grid) && visited[iNew][jNew] == false && grid[iNew][jNew] == grid[i][j]) {
            MarkID(iNew, jNew, grid, visited, idGrid, currId);
        }
    }

    return;
}


ull solve(vector<string>& vec) {

    const int m = vec.size();
    const int n = vec[0].size();

    unordered_map<int, int> area;
    unordered_map<int, int> perimeter;

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>>  idGrid(m, vector<int>(n, 0));

    int currId = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (visited[i][j] == false)
                MarkID(i, j, vec, visited, idGrid, currId++);

    for (auto row : idGrid) {
        for (auto num : row)
            cout << num << ' ';
        cout << '\n';
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            const int curr = idGrid[i][j];

            area[curr]++;

            for (int idx = 0; idx < 4; idx++) {
                int iNew = i + dirs[idx];
                int jNew = j + dirs[idx + 1];

                if (WithinBounds(iNew, jNew, idGrid)) {
                    perimeter[curr] += (idGrid[iNew][jNew] != curr);
                }
                else {
                    perimeter[curr]++;
                }
            }
        }
    }




    cout << currId << '\n';

    for (int i = 0; i < currId; i++) {
        cout << area[i] << " ";
    }
    cout << '\n';
    for (int i = 0; i < currId; i++) {
        cout << perimeter[i] << " ";
    }
    cout << '\n';


    
    
    ull res = 0;
    for (int i = 0; i < currId; i++)
        res += area[i] * perimeter[i];

    return res;
}


int main(void) {

    string line;
    vector<string> vec;
    while (getline(fin, line)) {
        vec.push_back(line);
    }

    cout << solve(vec);

    cout << endl;
    return 0;
}