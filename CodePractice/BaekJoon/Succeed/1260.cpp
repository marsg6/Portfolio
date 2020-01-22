#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void DFS(vector<vector<int>>& Graph, vector<bool>& Flags, const int CurrentNode) {
	Flags[CurrentNode] = true;
	cout << CurrentNode << " ";


	for (int i = 0; i < Graph[CurrentNode].size(); ++i) {
		int NextNode = Graph[CurrentNode][i];
		if (Flags[NextNode] == false) {
			DFS(Graph, Flags, NextNode);
		}
	}
}

void BFS(vector<vector<int>>& Graph, vector<bool>& Flags, const int StartNode) {
	queue<int> Q;
	Q.push(StartNode);
	Flags[StartNode] = true;

	while (!Q.empty()) {
		int CurrentNode = Q.front();
		Q.pop();
		cout << CurrentNode << " ";

		for (int i = 0; i < Graph[CurrentNode].size(); ++i) {
			int NextNode = Graph[CurrentNode][i];
			if (Flags[NextNode] == false) {
				Q.push(NextNode);
				Flags[NextNode] = true;
			}
		}
	}
}

int main() {
	int N, M, V;
	cin >> N >> M >> V;

	vector<vector<int>> GraphForDFS(N + 1, vector<int>());
	vector<vector<int>> GraphForBFS(N + 1, vector<int>());
	vector<bool> FlagsForDFS(N + 1, false);
	vector<bool> FlagsForBFS(N + 1, false);
	for (int i = 0; i < M; ++i) {
		int NodeA, NodeB;
		cin >> NodeA >> NodeB;
		GraphForDFS[NodeA].push_back(NodeB);
		GraphForDFS[NodeB].push_back(NodeA);
		GraphForBFS[NodeA].push_back(NodeB);
		GraphForBFS[NodeB].push_back(NodeA);
	}
	for (int i = 0; i < N + 1; ++i) {
		sort(GraphForDFS[i].begin(), GraphForDFS[i].end());
		sort(GraphForBFS[i].begin(), GraphForBFS[i].end());
	}

	DFS(GraphForDFS, FlagsForDFS, V);
	cout << endl;
	BFS(GraphForBFS, FlagsForBFS, V);
}