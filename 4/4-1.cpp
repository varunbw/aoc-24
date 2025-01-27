#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

ifstream fin("input.txt");
ofstream fout("output.txt");

array<pair<int, int>, 8> dirs = {
    pair<int, int>{ 0,  1},
    pair<int, int>{ 1,  1},
    pair<int, int>{ 1,  0},
    pair<int, int>{ 1, -1},
    pair<int, int>{ 0, -1},
    pair<int, int>{-1, -1},
    pair<int, int>{-1,  0},
    pair<int, int>{-1,  1}
};

bool WithinBounds(int i, int j, vector<string>& vec) {
    return (i >= 0 && i < vec.size() && 
            j >= 0 && j < vec[i].size());
}

ULL solve(vector<string>& vec) {

    ULL res = 0;
    string target = "XMAS";
    
    const int m = vec.size();
    const int n = vec[0].size();
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            const int iOld = i;
            const int jOld = j;
            
            for (const auto [iOff, jOff] : dirs) {
                i = iOld;
                j = jOld;
                
                int idx = 0;
                int count = target.size() + 1;
                while (count-- && WithinBounds(i, j, vec) && vec[i][j] == target[idx++]) {
                    i += iOff;
                    j += jOff;
                }

                if (count <= 0) {
                    res++;
                }
            }

            i = iOld;
            j = jOld;
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