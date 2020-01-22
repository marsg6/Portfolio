#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> res;

	for (int i = 0; i < commands.size(); ++i) {
		int start = commands[i][0];
		int end = commands[i][1];
		int target = commands[i][2];
		vector<int> subArr(array.begin() + start - 1, array.begin() + end);
		sort(subArr.begin(), subArr.end());
		res.emplace_back(subArr[target - 1]);
	}

	return res;
}