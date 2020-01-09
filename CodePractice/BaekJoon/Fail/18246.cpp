#include <iostream>
#include <vector>

using namespace std;

int Query(const vector<vector<int>>& Coord, int Max) {
	int ly, lx, ry, rx;
	cin >> ly >> lx >> ry >> rx;
	int max = 0;
	for (int y = ly; y < ry; ++y) {
		for (int x = lx; x < rx; ++x) {
			int curr = Coord[y][x];
			if (max < curr) {
				max = curr;
				if (max == Max) {
					return max;
				}
			}
		}
	}
	return max;
}

int main() {
	int N, M;
	cin >> N >> M;

	/* Coord[y][x] ==  Square from the coordinate (x, y) to the coordinate (x + 1, y + 1) */
	vector<vector<int>> Coord(1500, vector<int>(1500, 0));

	int max = 0;
	for (int i = 0; i < N; ++i) {
		/* 'l' means 'left' and 'r' means 'right' */
		int ly, lx, ry, rx;
		cin >> ly >> lx >> ry >> rx;

		for (int y = ly; y < ry; ++y) {
			for (int x = lx; x < rx; ++x) {
				/* Count */
				int tmp = ++Coord[y][x];
				if (max < tmp) {
					max = tmp;
				}
			}
		}
	}

	/* Query */
	for (int i = 0; i < M; ++i) {
		cout << Query(Coord, max) << endl;
	}
}