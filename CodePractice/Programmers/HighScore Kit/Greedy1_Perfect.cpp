#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	vector<int> jerseys(n + 1, 1);
	for (auto num : lost)		{ --jerseys[num]; }
	for (auto num : reserve)	{ ++jerseys[num]; }

	if (jerseys[1] == 2 && jerseys[2] == 0) { ++jerseys[2]; }
	for (int i = 2; i <= n - 1; ++i) {
		if (jerseys[i] == 2) {
			if (jerseys[i - 1] == 0) {
				++jerseys[i - 1];
			}
			else if (jerseys[i + 1] == 0) {
				++jerseys[i + 1];
			}
		}
	}
	if (jerseys[n] == 2 && jerseys[n - 1] == 0) { ++jerseys[n - 1]; }

	int count = 0;
	for (int i = 1; i <= n; ++i) {
		if (jerseys[i] != 0) {
			++count;
		}
	}
	return count;
}