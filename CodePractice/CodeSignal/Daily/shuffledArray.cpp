#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// https://app.codesignal.com/challenge/zBDDWvf2sHC7d3Dok

vector<int> shuffledArray(vector<int> shuffled) {
    auto sum = accumulate(shuffled.begin(), shuffled.end(), 0);
    sort(shuffled.begin(), shuffled.end());
    for (int i = 0; i < shuffled.size(); ++i) {
        if (sum - shuffled[i] == shuffled[i]) {
            shuffled.erase(shuffled.begin() + i);
            return shuffled;
        }
    }
}

int main() {
    for (auto v : shuffledArray({ 1, 12, 3, 6, 2 })) {
        cout << v << " ";
    }
    cout << endl; // { 1, 2, 3, 6 }

    for (auto v : shuffledArray({ 1, -3, -5, 7, 2 })) {
        cout << v << " ";
    }
    cout << endl; // { -5, -3, 2, 7 }
}