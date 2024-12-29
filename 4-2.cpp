#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

ifstream fin("input.txt");
ofstream fout("output.txt");

ULL solve(vector<string>& vec) {

    ULL res = 0;
    
    const int m = vec.size();
    const int n = vec[0].size();
    
    for (int i = 1; i < m - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (vec[i][j] == 'A'  &&
                (
                    (vec[i - 1][j - 1] == 'M' && vec[i + 1][j + 1] == 'S') ||
                    (vec[i - 1][j - 1] == 'S' && vec[i + 1][j + 1] == 'M')
                ) &&
                (
                    (vec[i + 1][j - 1] == 'M' && vec[i - 1][j + 1] == 'S') ||
                    (vec[i + 1][j - 1] == 'S' && vec[i - 1][j + 1] == 'M')
                )) {
                res ++;
            }
        }
    }

    return res;
}

int main(void) {

    vector<string> vec;
    string line;
    
    while (getline(fin, line)) {
        vec.push_back(line);
    }

    cout << solve(vec);

    cout << endl;
    return 0;
}