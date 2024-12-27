#include <bits/stdc++.h>

using namespace std;

int main(void) {

    ifstream fin("input.txt");

    int res = 0;

    string line;
    while (getline(fin, line)) {

        stringstream ss(line);

        vector<int> levels;
        int n;
        while (ss >> n) {
            levels.push_back(n);
        }

        const int size = levels.size();

        bool safe = true;

        if (levels[0] == levels[1]) {
            safe = false;
        }
        else if (levels[0] < levels[1]) {
            for (int i = 1; i < size; i++) {
                int diff = abs(levels[i - 1] - levels[i]);
                if (levels[i - 1] > levels[i] || diff > 3 || diff == 0) {
                    safe = false;
                    break;
                }
            }
        }
        else {
            for (int i = 1; i < size; i++) {
                int diff = abs(levels[i - 1] - levels[i]);
                if (levels[i - 1] < levels[i] || diff > 3 || diff == 0) {
                    safe = false;
                    break;
                }
            }
        }

        res += (int)safe;
        cout << (safe ? "safe" : "unsafe") << '\n';
    }

    cout << res;
    cout << endl;
    return 0;
}