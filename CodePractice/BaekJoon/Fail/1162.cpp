#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define INT_MAX 2147483647

using us = unsigned short;
using namespace std;

int SearchMinCost(vector<vector<int>>& Map, vector<tuple<us, us, int>>& LinkedCityList, vector<bool>& Flags) {
    us N = Map[0].size();
    int FinalMinCost = INT_MAX;
    do {
        for (us i = 0; i < Flags.size(); ++i) {
            if (Flags[i]) {
                us CityA = get<0>(LinkedCityList[i]);
                us CityB = get<1>(LinkedCityList[i]);

                Map[CityA - 1][CityB - 1] = 0;
                Map[CityB - 1][CityA - 1] = 0;
            }
        }

        vector<int> Costs(N, INT_MAX);
        us Start = 0, End = N - 1;
        Costs[Start] = 0;
        vector<bool> Visits(N, false);

        while (true) {
            int Min = INT_MAX;
            us CurrIndex;
            for (us i = 0; i < N; ++i) {
                if (!Visits[i] && Costs[i] < Min) {
                    Min = Costs[i];
                    CurrIndex = i;
                }
            }

            if (Min == INT_MAX) break;

            Visits[CurrIndex] = true;
            for (us i = 0; i < N; ++i) {
                int PossibleDist = Map[CurrIndex][i];
                if (PossibleDist != INT_MAX) {
                    int NewDist = PossibleDist + Costs[CurrIndex];
                    if (NewDist < Costs[i]) {
                        Costs[i] = NewDist;
                    }
                }
            }
        }

        if (Costs[End] < FinalMinCost) { FinalMinCost = Costs[End]; }

        for (us i = 0; i < Flags.size(); ++i) {
            if (Flags[i]) {
                us CityA = get<0>(LinkedCityList[i]);
                us CityB = get<1>(LinkedCityList[i]);
                int Cost = get<2>(LinkedCityList[i]);

                Map[CityA - 1][CityB - 1] = Cost;
                Map[CityB - 1][CityA - 1] = Cost;
            }
        }

    } while (next_permutation(Flags.begin(), Flags.end()));

    return FinalMinCost;
}

int main() {
    short N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> Map(N, vector<int>(N, INT_MAX));

    /* For combination */
    vector<tuple<us, us, int>> LinkedCityList;
    vector<bool> Flags(M, false);

    /* Map initalization */
    for (us i = 0; i < M; ++i) {
        us CityA, CityB;
        int Cost;
        cin >> CityA >> CityB >> Cost;
        Map[CityA - 1][CityB - 1] = Cost;
        Map[CityB - 1][CityA - 1] = Cost;

        /* For combination */
        LinkedCityList[i] = { CityA, CityB, Cost };
        if (M - K <= i) { Flags[i] = true; }
    }

    cout << SearchMinCost(Map, LinkedCityList, Flags);
}