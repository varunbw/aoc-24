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

/*
    Marks the id of the connected components in the grid
    @param i: row index
    @param j: col index
    @param grid: grid of characters
    @param visited: visited grid
    @param idGrid: grid of ids
    @param currId: current id
*/
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

/*
    Calculates the number of corners at a given point
    @param i: row index
    @param j: col index
    @param grid: grid of ids
    @return: number of corners at the given point
*/
int CalculateCornersAtPoint(int i, int j, const vector<vector<int>>& grid) {
    int count = 0;

    const int& curr = grid[i][j];

    // top left
    if (WithinBounds(i - 1, j, grid) && WithinBounds(i, j - 1, grid)) {
        const int& up = grid[i - 1][j];
        const int& left = grid[i][j - 1];
        const int& topLeft = grid[i - 1][j - 1];
        if (up != curr && left != curr) {
            count++;
        } else if (up == curr && left == curr) {
            count += (topLeft != curr);
        }
    }

    // top right
    if (WithinBounds(i - 1, j, grid) && WithinBounds(i, j + 1, grid)) {
        const int& up = grid[i - 1][j];
        const int& right = grid[i][j + 1];
        const int& topRight = grid[i - 1][j + 1];
        if (up != curr && right != curr) {
            count++;
        } else if (up == curr && right == curr) {
            count += (topRight != curr);
        }
    }

    // bottom left
    if (WithinBounds(i + 1, j, grid) && WithinBounds(i, j + 1, grid)) {
        const int& down = grid[i + 1][j];
        const int& right = grid[i][j + 1];
        const int& bottomRight = grid[i + 1][j + 1];
        if (down != curr && right != curr) {
            count++;
        } else if (down == curr && right == curr) {
            count += (bottomRight != curr);
        }
    }

    // bottom right
    if (WithinBounds(i + 1, j, grid) && WithinBounds(i, j - 1, grid)) {
        const int& down = grid[i + 1][j];
        const int& left = grid[i][j - 1];
        const int& bottomLeft = grid[i + 1][j - 1];
        if (down != curr && left != curr) {
            count++;
        } else if (down == curr && left == curr) {
            count += (bottomLeft != curr);
        }
    }

    return count;
}

/*
    Calculates the number of corners in the grid
    @param idGrid: grid of ids
    @return: grid of corners
*/
vector<vector<int>> CalculateCorners(vector<vector<int>>& idGrid) {
    const int m = idGrid.size();
    const int n = idGrid[0].size();

    vector<vector<int>> cornerCount(m, vector<int>(n, 0));

    // Mark corners of the grid as 1
    cornerCount[0][0] = 1;
    cornerCount[0][n - 1] = 1;
    cornerCount[m - 1][0] = 1;
    cornerCount[m - 1][n - 1] = 1;

    // Calculate corners for the first and last col
    for (int i = 1; i < m; i++) {
        if (idGrid[i][0] != idGrid[i - 1][0]) {
            cornerCount[i][0]++;
            cornerCount[i - 1][0]++;
        }
        if (idGrid[i][n - 1] != idGrid[i - 1][n - 1]) {
            cornerCount[i][n - 1]++;
            cornerCount[i - 1][n - 1]++;
        }
    }

    // Caclulate corners for the first and last row
    for (int j = 1; j < n; j++) {
        if (idGrid[0][j] != idGrid[0][j - 1]) {
            cornerCount[0][j]++;
            cornerCount[0][j - 1]++;
        }
        if (idGrid[m - 1][j] != idGrid[m - 1][j - 1]) {
            cornerCount[m - 1][j]++;
            cornerCount[m - 1][j - 1]++;
        }
    }

    // Calculate corners for the rest of the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cornerCount[i][j] += CalculateCornersAtPoint(i, j, idGrid);
        }
    }

    return cornerCount;
}


ull solve(vector<string>& vec) {

    const int m = vec.size();
    const int n = vec[0].size();
    
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>>  idGrid(m, vector<int>(n, 0));
    
    // Mark the id of the connected components
    int maxId = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (visited[i][j] == false)
                MarkID(i, j, vec, visited, idGrid, maxId++);
    
    // Calculate the area of each patch
    unordered_map<int, int> area;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            area[idGrid[i][j]]++;
        }
    }

    vector<vector<int>>  cornerCount = CalculateCorners(idGrid);
    
    // Calculate the number of sides of each patch
    unordered_map<int, int> sides;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sides[idGrid[i][j]] += cornerCount[i][j];
        }
    }

    ull res = 0;
    for (int i = 0; i < maxId; i++)
        res += area[i] * sides[i];

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