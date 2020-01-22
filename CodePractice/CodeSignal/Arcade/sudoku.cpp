#include <iostream>
#include <vector>

using namespace std;

//https://app.codesignal.com/arcade/intro/level-12/tQgasP8b62JBeirMS

bool sudoku(vector<vector<int>> grid) {
	vector<int> Check(10, 0);
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			++Check[grid[i][j]];
		}
		int Count = Check[1];
		for (int j = 2; j < 10; ++j) {
			if (Check[j] != Count) {
				return false;
			}
		}
	}
	for (int j = 0; j < grid.size(); ++j) {
		for (int i = 0; i < grid[j].size(); ++i) {
			++Check[grid[i][j]];
		}
		int Count = Check[1];
		for (int i = 2; i < 10; ++i) {
			if (Check[i] != Count) {
				return false;
			}
		}
	}
	for (int i = 0; i < grid.size(); i += 3) {
		for (int j = 0; j < grid[i].size(); j += 3) {
			for (int k = i; k < i + 3; ++k) {
				for (int l = j; l < j + 3; ++l) {
					++Check[grid[k][l]];
				}
			}
			cout << endl;
			int Count = Check[1];
			for (int k = 2; k < 10; ++k) {
				if (Check[k] != Count) {
					return false;
				}
			}
		}
	}

	return true;
}

int main() {
	sudoku(vector<vector<int>>{ { 1, 3, 2, 5, 4, 6, 9, 8, 7 },
						{ 4, 6, 5, 8, 7, 9, 3, 2, 1 },
						{ 7, 9, 8, 2, 1, 3, 6, 5, 4 },
						{ 9, 2, 1, 4, 3, 5, 8, 7, 6 },
						{ 3, 5, 4, 7, 6, 8, 2, 1, 9 },
						{ 6, 8, 7, 1, 9, 2, 5, 4, 3 },
						{ 5, 7, 6, 9, 8, 1, 4, 3, 2 },
						{ 2, 4, 3, 6, 5, 7, 1, 9, 8 },
						{ 8, 1, 9, 3, 2, 4, 7, 6, 5 }});
}