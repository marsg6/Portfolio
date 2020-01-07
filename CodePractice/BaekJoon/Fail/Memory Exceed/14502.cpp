#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

void BruteBuild(vector<vector<int>>& Areas, int& BuiltWalls, int& CurrentSafeAreas) {
	int i_size = Areas.size();
	int j_size = Areas[0].size();

	for (int i = 0; i < i_size; ++i) {
		for (int j = 0; j < j_size; ++j) {
			if (Areas[i][j] == 0) {
				Areas[i][j] = 3;

			}
		}
	}
}

void BuildWalls(vector<vector<int>>& Areas, int& BuiltWalls, int& CurrentSafeAreas) {
	int i_size = Areas.size();
	int j_size = Areas[0].size();

	for (int i = 0; i < i_size; ++i) {
		for (int j = 0; j < j_size; ++j) {
			if (Areas[i][j] == 0) {
				Areas[i][j] = 3;
				if (CurrentSafeAreas < SafeAreas(Areas)) {
					CurrentSafeAreas = SafeAreas(Areas);
					++BuiltWalls;
					BuildWalls(Areas, BuiltWalls, CurrentSafeAreas);
				}
				else {
					Areas[i][j] = 0;
				}
			}
		}
	}
}

int SafeAreas(vector<vector<int>> Areas) {
	array<int, 4> di{ -1, 0, 1, 0 };
	array<int, 4> dj{ 0, 1, 0, -1 };

	int i_size = Areas.size();
	int j_size = Areas[0].size();

	int DangerAreas = 0, SafeAreas = 0;

	for (int i = 0; i < i_size; ++i) {
		for (int j = 0; j < j_size; ++j) {
			if (Areas[i][j] == 2 || Areas[i][j] == 4) {
				for (int k = 0; k < 4; ++k) {
					int ni = i + di[k];
					int nj = j + dj[k];

					if (0 <= ni && 0 <= nj && ni < i_size && nj < j_size) {
						if (Areas[ni][nj] == 0) {
							Areas[ni][nj] = 4;
							++DangerAreas;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < i_size; ++i) {
		for (int j = 0; j < j_size; ++j) {
			if (Areas[i][j] == 0) {
				++SafeAreas;
			}
		}
	}

	return SafeAreas;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<int>> Areas(N, vector<int>(M, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> Areas[i][j];
		}
	}
	
	int TotalSafeAreas = 0;
	int CurrentSafeAreas = SafeAreas(Areas);
	int BuiltWalls = 0;

	BuildWalls(Areas, BuiltWalls, CurrentSafeAreas);

	

}