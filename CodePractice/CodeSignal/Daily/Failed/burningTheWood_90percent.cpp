#include <iostream>
#include <vector>

using namespace std;

//https://app.codesignal.com/challenge/ns25kwheaFf9WLZ45

void rec(const vector<vector<int>>& graph, vector<bool>& checks, int node, int k) {
	if (k == -1) { return; }
	if (checks[node]) { return; }
	checks[node] = true;

	for (auto next : graph[node]) {
		rec(graph, checks, next, k - 1);
	}
}

vector<int> burningTheWood(int n, vector<vector<int>> wmap, int start, int k) {
	vector<bool> checks(n, false);
	vector<vector<int>> graph(n);
	for (const auto& road : wmap) {
		graph[road[0]].emplace_back(road[1]);
		graph[road[1]].emplace_back(road[0]);
	}

	rec(graph, checks, start, k);

	vector<int> res;
	for (int i = 0; i < n; ++i) {
		if (checks[i]) {
			res.emplace_back(i);
		}
	}
	return res;
}