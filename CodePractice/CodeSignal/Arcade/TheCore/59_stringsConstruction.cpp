#include <iostream>
#include <vector>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/mirror-lake/chW9F8bCgxYJBcgj3

int stringsConstruction(string a, string b) {
	vector<pair<int, int>> counts(26, {0, 0});
	for (const auto& c : a) {
		++counts[c - 'a'].first;
	}
	for (const auto& c : b) {
		++counts[c - 'a'].second;
	}

	int min = INT_MAX;
	for (const auto& p : counts) {
		if (p.first && (p.second / p.first) < min) {
			min = (p.second / p.first);
		}
	}
	return min;
}

int main() {
	cout << stringsConstruction("abc", "abccba") << endl; // 2
	cout << stringsConstruction("ab", "abccba") << endl; // 2
}