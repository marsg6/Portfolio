#include <iostream>
#include <vector>
#include <algorithm>

#define INT_MAX 2147483647

using namespace std;

/* 다익스트라 */
void Search(vector<vector<int>>& Towns, int StartTown, int EndTown, int LeftTown, int RightTown) {
	int TownNum = Towns.size();

	/* 도로 끊기... */
	int LostRouteCost = Towns[LeftTown - 1][RightTown - 1];
	Towns[LeftTown - 1][RightTown - 1] = INT_MAX;
	Towns[RightTown - 1][LeftTown - 1] = INT_MAX;

	vector<bool> Checks(TownNum, false);
	vector<int> Costs(TownNum, INT_MAX);
	Costs[StartTown - 1] = 0;

	while (true) {
		int MinCost = INT_MAX;
		int MinCostIndex;
		for (int i = 0; i < TownNum; ++i) {
			if (!Checks[i] && Costs[i] < MinCost) {
				MinCost = Costs[i];
				MinCostIndex = i;
			}
		}

		/* No Possibility */
		if (MinCost == INT_MAX) break;

		/* Visit */
		Checks[MinCostIndex] = true;
		for (int i = 0; i < TownNum; ++i) {
			int PossibleRouteCost = Towns[MinCostIndex][i];
			if (PossibleRouteCost != INT_MAX) {
				int NewCost = PossibleRouteCost + Costs[MinCostIndex];
				if (NewCost < Costs[i]) {
					Costs[i] = NewCost;
				}
			}
		}
	}

	int TotalCost = Costs[EndTown - 1];
	if (TotalCost == INT_MAX) cout << -1 << endl;
	else cout << TotalCost << endl;

	Towns[LeftTown - 1][RightTown - 1] = LostRouteCost;
	Towns[RightTown - 1][LeftTown - 1] = LostRouteCost;
}

int main() {
	/* Initial Input */
	int TownNum, RoadNum, BitTown, HexTown;
	cin >> TownNum >> RoadNum >> BitTown >> HexTown;

	/* Make Town List */
	vector<vector<int>> Towns;
	for (int i = 0; i < TownNum; ++i) {
		vector<int> Town(TownNum, INT_MAX);
		Towns.push_back(Town);
	}


	/* Road Info Input */
	for (int i = 0; i < RoadNum; ++i) {
		int TownA, TownB, Cost;
		cin >> TownA >> TownB >> Cost;

		Towns[TownA - 1][TownB - 1] = Cost;
		Towns[TownB - 1][TownA - 1] = Cost;
	}

	int k;
	cin >> k;
	vector<int> Routes;

	for (int i = 0; i < k; ++i) {
		int Route;
		cin >> Route;
		Routes.push_back(Route);
	}

	for (int i = 0; i < k - 1; ++i) {
		Search(Towns, BitTown, HexTown, Routes[i], Routes[i + 1]);
	}
}