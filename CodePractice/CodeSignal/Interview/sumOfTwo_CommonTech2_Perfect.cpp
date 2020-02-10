#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

//https://app.codesignal.com/interview-practice/task/Hm98RnqK9Be575yoj

bool sumOfTwo(vector<int> a, vector<int> b, int v) {
	unordered_set<int> sa(a.begin(), a.end());
	unordered_set<int> sb(b.begin(), b.end());

	for (const auto& s : sa) {
		if (sb.find(v - s) != sb.end()) {
			return true;
		}
	}

	return false;
}

int main() {
	cout << sumOfTwo({ 1, 2, 3 }, { 10, 20, 30, 40 }, 42) << endl; // true
	cout << sumOfTwo({ 1, 2, 3 }, { 10, 20, 30, 40 }, 50) << endl; // false
}