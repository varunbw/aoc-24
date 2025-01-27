#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<int> MakeDisk(string& diskmap) {

    ull totalSize = 0;
    for (char c : diskmap) 
        totalSize += c - '0';

    vector<int> disk(totalSize, -1);

    int id = 0;
    int diskIdx = 0;
    bool isData = true;
    for (char c : diskmap) {
        int num = c - '0';
        if (isData) {
            while (num--) 
                disk[diskIdx++] = id;
            
            id++;
        }
        else 
            diskIdx += num;

        isData = !isData;
    }

    return disk;
}

void CompactDisk(vector<int>& disk) {

    const int n = disk.size();

    struct Block {
        int id;
        int size;
        int idx;
        bool isFree;
    };

    vector<Block> blocks;

    int ptr = 0;
    while (ptr < n) {
        Block block;
        
        int right = ptr;
        while (right < n && disk[right] == disk[ptr])
            right++;
        
        block.id = disk[ptr];
        block.size = right - ptr;
        block.idx = ptr;
        block.isFree = false;

        int freeSpaceLeft = right;

        while (right < n && disk[right] == -1)
            right++;
        
        ptr = right;
        int freeSpaceRight = ptr - 1;

        Block freeBlock;
        freeBlock.id = -1;
        freeBlock.size = freeSpaceRight - freeSpaceLeft + 1;
        freeBlock.idx = freeSpaceLeft;
        freeBlock.isFree = true;

        if (block.size)
            blocks.push_back(block);
        if (freeBlock.size)
            blocks.push_back(freeBlock);
    }
    
    const int numOfBlocks = blocks.size();
    for (int i = numOfBlocks - 1; i >= 0; i--) {

        Block& block = blocks[i];

        if (block.id == -1)
            continue;

        const int currSize = block.size;
        for (int j = 0; j < numOfBlocks; j++) {
            Block& freeBlock = blocks[j];

            if (freeBlock.isFree == false || freeBlock.size < currSize)
                continue;

            if (freeBlock.idx >= block.idx)
                break;

            block.idx = freeBlock.idx;
            freeBlock.idx = block.idx + currSize;
            freeBlock.size -= currSize;

            break;
        }
    }

    fill(disk.begin(), disk.end(), -1);

    for (int i = 0; i < blocks.size(); i++) {
        int idx = blocks[i].idx;
        int id = blocks[i].id;
        int size = blocks[i].size;

        // cout << "ID: " << id
        //     << ", Size: " << size
        //     << ", IDX: " << idx
        //     << ", IsFree: " << blocks[i].isFree << '\n';

        if (!blocks[i].isFree) 
            for (int j = idx; j < idx + size; j++) 
                disk[j] = id;
    }

    return;
}

unsigned long long solve(string& diskmap) {

    vector<int> disk = MakeDisk(diskmap);
    CompactDisk(disk);

    ull res = 0;
    const int n = disk.size();
    for (int i = 0; i < n; i++) 
        if (disk[i] != -1)
            res += i * (disk[i]);
    
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