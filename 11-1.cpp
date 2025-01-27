#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long

ifstream fin("input.txt");
ofstream fout("output.txt");

ull solve(vector<ull>& vec) {

    ull res = vec.size();

    ull count = 75;
    while (count--) {
        cout << count << '\n';
        vector<ull> toAdd;
        for (ull i = 0; i < vec.size(); i++) {

            string str = to_string(vec[i]);

            if (vec[i] == 0) {
                vec[i] = 1;
            }
            else if (str.size() % 2 == 0) {
                string half(str.begin(), str.begin() + (str.size() / 2));
                toAdd.push_back(stoull(half));

                half = string(str.begin() + (str.size() / 2), str.end());
                toAdd.push_back(stoull(half));
                vec.erase(vec.begin() + i);
                i--;
            }
            else {
                toAdd.push_back(vec[i] * 2024);
                vec.erase(vec.begin() + i);
                i--;
            }

        }
        for (ull num : toAdd)
            vec.push_back(num);
        
        for (ull num : vec) {
            // cout << num << " ";
        }
        // cout << "\n";
    }

    return vec.size();
}


int main(void) {

    string line;
    vector<ull> vec;
    ull n;
    while (fin >> n) {
        vec.push_back(n);
    }

    ull res = solve(vec);

    cout << res << '\n';

    cout << endl;
    return 0;
}