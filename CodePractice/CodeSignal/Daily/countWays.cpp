#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://app.codesignal.com/challenge/rbwtuZjSG8zJQszCz

int twoArraysNthElement(vector<int> array1, vector<int> array2, int n) {

	int Index1 = 0, Index2 = 0;
	int Count = 0;
	int Current = 0;

	if (array2.size() == 0) {
		array2.push_back(INT_MAX);
	}
	if (array1.size() == 0) {
		array1.push_back(INT_MAX);
	}

	while (Count <= n) {
		if (array1[Index1] < array2[Index2]) {
			Current = array1[Index1];
			++Index1;
			if (array1.size() == Index1) {
				array1.push_back(INT_MAX);
			}
		}
		else {
			Current = array2[Index2];
			++Index2;
			if (Index2 == array2.size()) {
				array2.push_back(INT_MAX);
			}
		}
		++Count;
	}
	return Current;
}

int main() {
	cout << twoArraysNthElement({ 1, 3, 4 }, { 2, 6, 8 }, 5) << endl; // 8
	cout << twoArraysNthElement({ 1, 2, 3 }, { 4, 5, 6 }, 3) << endl; // 4
}