#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://app.codesignal.com/challenge/KkRXXEt9DwaHFYk2K

bool isCryptSolution(vector<string> crypt, vector<vector<char>> solution) {
	vector<long> vec(3, 0);
	for (int i = 0; i < crypt.size(); ++i) {
		for (auto s : crypt[i]) {
			vec[i] *= 10;
			vec[i] += (*find_if(solution.begin(), solution.end(), [s](auto v) { return v[0] == s; }))[1] - '0';
		}
		int digitNum = vec[i] ? log10(vec[i]) : 0;
		if (digitNum + 1 < crypt[i].size()) {
			return false;
		}
	}
	return vec[0] + vec[1] == vec[2];
}


int main() {
	cout << isCryptSolution({ "SEND", "MORE", "MONEY" }, { {'O', '0'}, {'M', '1'}, {'Y', '2'}, {'E', '5'}, {'N', '6'}, {'D', '7'}, {'R', '8'}, {'S', '9'} }) << endl; // true
}