#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

template <typename T>
void Print1DVector(const std::vector<T>& vec, std::ostream& stream = std::cout) {

    const int n = vec.size();

    
    if (n)
        stream << vec[0] << '\n';
        
    for (int i = 1; i < n; i++)
        stream << vec[i] << '\n';

    stream << "\n";
    return;
}

bool WithinBounds(int i, int j, vector<string>& vec) {
    return i >= 0 && i < vec.size() &&
           j >= 0 && j < vec[0].size();
}

ull solve(vector<string>& vec) {

    unordered_map<char, vector<pair<int, int>>> coordinates;

    const int m = vec.size();
    const int n = vec[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vec[i][j] != '.')
                coordinates[vec[i][j]].push_back(make_pair(i, j));
        }
    }

    set<pair<int, int>> antinodes;
    for (auto& [freq, coords] : coordinates) {
        const int s = coords.size();

        for (int i = 0; i < s; i++) {
            pair<int, int>& curr = coords[i];
            
            for (int j = i + 1; j < s; j++) {
                pair<int, int>& next = coords[j];

                const int iDiff = next.first - curr.first ;
                const int jDiff = next.second - curr.second;

                int iAheadOfNext = next.first + iDiff;
                int jAheadOfNext = next.second + jDiff;
                if (WithinBounds(iAheadOfNext, jAheadOfNext, vec)) 
                    antinodes.insert(make_pair(iAheadOfNext, jAheadOfNext));
                
                int iBehindCurr = curr.first - iDiff;
                int jBehindCurr = curr.second - jDiff;
                if (WithinBounds(iBehindCurr, jBehindCurr, vec)) 
                    antinodes.insert(make_pair(iBehindCurr, jBehindCurr));
            }
        }
    }

    return antinodes.size();
}

int main(void) {
    
    vector<string> vec;
    string line;
    while (getline(fin, line)) {
        vec.push_back(line);
    }

    ull res = solve(vec); 
    cout << res;

    cout << endl;
    return 0;
}