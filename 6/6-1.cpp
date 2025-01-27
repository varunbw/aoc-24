#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

pair<int, int> GetStartingPosition(vector<vector<char>>& vec) {

    int iRes = 0;
    int jRes = 0;

    const int m = vec.size();
    const int n = vec[0].size();

    for (int i = 0; i < m && iRes == 0; i++) {
        for (int j = 0; j < n && jRes == 0; j++) {
            if (vec[i][j] == '^') {
                iRes = i;
                jRes = j;
                break;
            }
        }
    }

    return make_pair(iRes, jRes);
}

bool WithinBounds(int i, int j, int m, int n) {
    return i >= 0 && j >= 0 && i < m && j < n;
}


unsigned long long solve(vector<vector<char>>& vec) {

    auto const [iStart, jStart] = GetStartingPosition(vec);

    // Up, Down, Left, Right (U, D, L, R respectively)
    char dir = 'U';

    const int m = vec.size();
    const int n = vec[0].size();

    int i = iStart;
    int j = jStart;
    while (WithinBounds(i, j, m, n)) {
        vec[i][j] = 'X';
        switch (dir) {
            case 'U':
                if (WithinBounds(i - 1, j, m, n) && vec[i - 1][j] == '#') 
                    dir = 'R';
                else 
                    i--;
                break;

            case 'D':
                if (WithinBounds(i + 1, j, m, n) && vec[i + 1][j] == '#') 
                    dir = 'L';
                else 
                    i++;
                break;
            
            case 'L':
                if (WithinBounds(i, j - 1, m, n) && vec[i][j - 1] == '#') 
                    dir = 'U';
                else 
                    j--;
                break;

            case 'R':
                if (WithinBounds(i, j + 1, m, n) && vec[i][j + 1] == '#') 
                    dir = 'D';
                else 
                    j++;
                break;

            default:
                cout << "[????????]: How did we get here\n";
        }
    }

    unsigned long long res = 0;
    for (auto& row : vec) {
        for (auto& c : row) {
            if (c == 'X')
                res++;
        }
    }

    return res;
}

int main(void) {

    string line;

    vector<vector<char>> vec;
    while (getline(fin, line)) {
        vector<char> row;
        row.reserve(line.size());
        for (char c : line) {
            row.push_back(c);
        }

        vec.push_back(row);
    }

    unsigned long long res = solve(vec);
    cout << res;

    cout << endl;
    return 0;
}