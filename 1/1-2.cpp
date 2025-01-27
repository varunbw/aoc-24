#include <bits/stdc++.h>

using namespace std;

#define T 1000

int main(void) {

    ifstream fin("input.txt");

    int t = T;
    int res = 0;

    array<int, 1000> a;
    unordered_map<int, int> b;
    int idx = 0;
    
    while (t--) {
        fin >> a[idx++];

        int n;
        fin >> n;
        b[n]++;
    }

    for (int i = 0; i < T; i++) {
        res += a[i] * b[a[i]];
    }

    cout << res;

    cout << endl;
    return 0;
}