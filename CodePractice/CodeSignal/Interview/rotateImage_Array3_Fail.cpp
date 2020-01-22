#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<vector<int>> rotateImage(vector<vector<int>> a) {
	int n = a.size();
	for (int i = 0; i < n / 2; ++i) {
		for (int j = i; j < n - i; ++j) {
			// i, j
			array<int, 4> dy{ j, n - 1 - i, n - 1 - j, i };
			array<int, 4> dx{ n - 1 - i, n - 1 - j, i, j};
			int curr = a[i][j];
			int temp;
			for (int k = 0; k < 4; ++k) {
				temp = a[dy[k]][dx[k]];
				a[dy[k]][dx[k]] = curr;
				curr = temp;
			}
		}
	}
	return a;
}

int main() {
	cout << firstNotRepeatingCharacter("abacabad") << endl; // c
	cout << firstNotRepeatingCharacter("abacabaabacaba") << endl; // _
}