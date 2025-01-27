#include <bits/stdc++.h>

using namespace std;

#define T 1000

int main(void) {

    ifstream fin("input.txt");

    int t = 1000;
    int res = 0;

    array<int, 1000> a;
    array<int, 1000> b;
    int idx = 0;
    
    while (t--) {
        fin >> a[idx] >> b[idx++];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < 1000; i++) {
        res += abs(a[i] - b[i]);
    }

    cout << res;

    cout << endl;
    return 0;
}