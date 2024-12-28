#include <bits/stdc++.h>
using namespace std;

unsigned long long solve(string& line) {

    regex pattern(R"(mul\((\d+),(\d+)\))");
    smatch match;

    unsigned long long res = 0;
    while (regex_search(line, match, pattern)) {
        res += stoi(match[1].str()) * stoi(match[2].str());

        string matchedPart = match[0].str();
        line.erase(line.begin(), line.begin() + line.find(matchedPart) + matchedPart.size());
    }

    return res;
}

int main(void) {

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    unsigned long long res = 0;

    string line;
    while (getline(fin, line)) {
        res += solve(line);
    }

    cout << res;
    cout << endl;
    return 0;
}