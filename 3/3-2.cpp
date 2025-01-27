#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

unsigned long long solve(string& line) {
    regex pattern(R"(do\(\)|don't\(\)|mul\((\d+),(\d+)\))");
    smatch match;

    bool countTowardsResult = true;
    unsigned long long res = 0;
    auto start = line.cbegin();

    while (regex_search(start, line.cend(), match, pattern)) {
        string matchStr = match[0].str();

        if (matchStr == "do()") {
            countTowardsResult = true;
        }
        else if (matchStr == "don't()") {
            countTowardsResult = false; 
        }
        else if (matchStr.find("mul") == 0) {
            if (countTowardsResult) {
                res += stoi(match[1].str()) * stoi(match[2].str());
            }
        }

        start += match.position() + match.length();
    }

    return res;
}

int main(void) {

    string line;
    getline(fin, line);
    cout << solve(line);

    cout << endl;
    return 0;
}