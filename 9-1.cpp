#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

template <typename T>
void Print1DVector(const std::vector<T>& vec, std::ostream& stream = std::cout) {

    const int n = vec.size();

    stream << '[';
    
    if (n)
        stream << vec[0];
        
    for (int i = 1; i < n; i++)
        stream << ", " << vec[i];

    stream << "]\n";
    return;
}

vector<int> MakeDisk(string& diskmap) {

    ull totalSize = 0;
    for (char c : diskmap) {
        totalSize += c - '0';
    }

    // string disk(totalSize, '.');
    vector<int> disk(totalSize, -1);

    int id = 0;
    int diskIdx = 0;
    bool isData = true;
    // 12345
    for (char c : diskmap) {
        int num = c - '0';
        if (isData) {
            while (num--) {
                disk[diskIdx++] = id;
            }
            id++;
        }
        else {
            diskIdx += num;
        }

        isData = !isData;
    }

    cout << "ID: " << id << '\n'; 
    // fout << "Disk: " << disk << '\n';
    Print1DVector(disk, fout);
    return disk;
}

void CompactDisk(vector<int>& disk) {
    int left  = 0;
    int right = disk.size() - 1;

    while (left <= right && disk[left] != -1)
        left++;
    
    while (left < right) {
        disk[left]  = disk[right];
        disk[right] = -1;
        right--;
        left++;

        while (disk[left] != -1)
            left++;
        while (disk[right] == -1)
            right--;
    }

    // fout << "Comp: " << disk;
    return;
}


unsigned long long solve(string& diskmap) {

    vector<int> disk = MakeDisk(diskmap);
    CompactDisk(disk);

    ull res = 0;
    const int n = disk.size();
    for (int i = 0; i < n && disk[i] != -1; i++) {
        res += i * (disk[i]);
    }
    
    return res;
}

int main(void) {

    string line;
    getline(fin, line);

    ull res = solve(line);

    cout << '\n' << res << '\n';
    cout << endl;
    return 0;
}