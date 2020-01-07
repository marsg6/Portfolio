#include <iostream>
#include <vector>

using namespace std;

void CalDistance_Rep(int N, int M, int Dist, vector<vector<char>>& Maze, vector<vector<int>>& Distances) {
	if (Maze[N][M] == '0') return;
	if (Dist < Distances[N][M]) {
		Distances[N][M] = Dist;
		Maze[N][M] = 0;
	}
	else return;

	if (0 <= N - 1)					CalDistance_Rep(N - 1, M, Dist + 1, Maze, Distances);
	if (N + 1 < Maze.size())		CalDistance_Rep(N + 1, M, Dist + 1, Maze, Distances);
	if (0 <= M - 1)					CalDistance_Rep(N, M - 1, Dist + 1, Maze, Distances);
	if (M + 1 < Maze[0].size())		CalDistance_Rep(N, M + 1, Dist + 1, Maze, Distances);
}

int main() {
	vector<vector<char>> Maze;
	vector<vector<int>> Distances;

	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		Maze.emplace_back(vector<char>());
		Distances.emplace_back(vector<int>());
		for (int j = 0; j < M; ++j) {
			char IsOpen;
			cin >> IsOpen;
			Maze[i].push_back(IsOpen);
			Distances[i].push_back(1000000);
		}
	}

	CalDistance_Rep(N - 1, M - 1, 1, Maze, Distances);

	cout << Distances[0][0];
}