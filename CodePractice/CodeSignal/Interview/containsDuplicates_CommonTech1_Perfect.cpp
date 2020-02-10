#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://app.codesignal.com/interview-practice/task/CfknJzPmdbstXhsoJ

bool containsDuplicates(vector<int> a) {
	size_t origin = a.size();
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	return origin != a.size();
}

int main() {
	cout << containsDuplicates({ 1, 2, 3, 1 }) << endl; // true
	cout << containsDuplicates({ 3, 1 }) << endl; // false
}