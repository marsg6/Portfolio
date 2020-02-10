#include <iostream>
#include <vector>
#include <set>

using namespace std;

//https://app.codesignal.com/challenge/Bv5azAPGvcGWqEvq8


// test17 time limit error
int surpasserCount(vector<int> a) {
	int res = 0;

	multiset<int> b;
	for (int i = a.size() - 1; 0 <= i; --i) {
		b.emplace(a[i]);
		res += distance(b.find(a[i]), b.end()) - b.count(a[i]);
		res %= 1000000007;
	}
	return res;
}

// test19 time limit error
int surpasserCount(vector<int> a) {
	int res = 0;

	for (int i = a.size() - 1; 0 <= i; --i) {
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i]) {
				++res;
			}
		}
		res %= 1000000007;
	}
	return res;
}

// test19 time limit error
int surpasserCount(vector<int> a) {
	int res = 0;

	for (int i = a.size() - 2; 0 <= i; --i) {
		for (int j = i; j < a.size() - 1; ++j) {
			if (a[j + 1] <= a[j]) {
				swap(a[j], a[j + 1]);
			}
			else {
				res += a.size() - 1 - j;
				break;
			}
		}
		res %= 1000000007;
	}
	return res;
}

int main() {
	cout << surpasserCount({ 1, 2, 3, 4, 5 }) << endl; // 10
	cout << surpasserCount({ 54, 11, 58 }) << endl; // 2
}