#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long

ifstream fin("input.txt");
ofstream fout("output.txt");

ull solve(unordered_map<ull, ull>& freq) {

    int blinks = 75;
    for (int i = 0; i < blinks; i++) {

        unordered_map<ull, ull> nextFreq;

        for (auto& [num, count] : freq) {
            string str = to_string(num);

            if (num == 0)
                nextFreq[1] += count;
            else if (str.size() % 2 == 0) {
                nextFreq[stoull(str.substr(0, str.size() / 2))] += count;
                nextFreq[stoull(str.substr(str.size() / 2, str.size()))] += count;
            }
            else
                nextFreq[num * 2024] += count;
        }
        
        freq = move(nextFreq);
    }

    ull res = 0;
    for (auto& [num, count] : freq)
        res += count;

    return res;
}


int main(void) {

    string line;
    unordered_map<ull, ull> freq;
    ull n;
    while (fin >> n) {
        freq[n]++;
    }

    ull res = solve(freq);

    cout << res << '\n';

    cout << endl;
    return 0;
}