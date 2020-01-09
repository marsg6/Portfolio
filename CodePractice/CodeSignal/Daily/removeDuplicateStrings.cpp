#include <iostream>
#include <vector>

using namespace std;

// https://app.codesignal.com/challenge/pC6LK4Ne2jHjP74Ew

vector<string> removeDuplicateStrings(vector<string> inputArray) {
	string CurrentStr = inputArray[0];

	auto It = inputArray.begin() + 1;
	for (int i = 1; i < inputArray.size(); ++i) {
		if (inputArray[i] == CurrentStr) {
			inputArray.erase(inputArray.begin() + i);
			--i;
		}
		else {
			CurrentStr = inputArray[i];
		}
	}

	return inputArray;
}

int main() {
	auto strs = removeDuplicateStrings({ "a", "a", "ab", "ab", "abc" });
	
	for (auto str : strs) {
		cout << str << " ";
	}
	cout << endl;
	
	strs = removeDuplicateStrings({ "a", "a", "a" });
	for (auto str : strs) {
		cout << str << " ";
	}
	cout << endl;
}