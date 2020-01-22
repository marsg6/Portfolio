#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://app.codesignal.com/challenge/J785w3Xu4BFzqnREg

int numbersGrouping(vector<int> a) {
	int size = a.size();
	for (auto& n : a) {
		n = (n - 1) / pow(10, 4);
	}
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());

	return size + a.size();
}

int main() {
	cout << numbersGrouping({ 20000, 239, 10001, 999999, 10000, 20566, 29999 }) << endl; // 11
	cout << numbersGrouping({ 10000, 20000, 30000, 40000, 50000, 60000, 10000, 120000, 150000, 200000, 300000, 1000000, 10000000, 100000000, 10000000 }) << endl; // 28
}