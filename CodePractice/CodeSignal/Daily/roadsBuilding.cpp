#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://app.codesignal.com/challenge/ZmCxmJRGWNxMohBs5

vector<vector<int>> roadsBuilding(int cities, vector<vector<int>> roads) {
	vector<vector<int>> routes(cities);
	for (const auto& road : roads) {
		int start = min(road[0], road[1]);
		int end = max(road[0], road[1]);
		routes[start].emplace_back(end);
	}

	vector<vector<int>> res;
	for (int i = 0; i < cities; ++i) {
		sort(routes[i].begin(), routes[i].end());
		int k = i + 1;
		int j = 0;
		while (k < cities) {
			if (j == routes[i].size()) {
				res.emplace_back(vector<int>{i, k});
				++k;
				continue;
			}
			if (routes[i][j] != k) {
				res.emplace_back(vector<int>{i, k});
			}
			else {
				++j;
			}
			++k;
		}
	}
	return res;
}

int main() {

}