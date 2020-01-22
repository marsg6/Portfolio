#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// https://app.codesignal.com/challenge/ueMWmccxYbti63LXA

int sameNum(string str) {
	int Count = 0;
	if (str[0] == str[1] || str[1] == str[2] || str[2] == str[0]) {
		Count = 1;
		if (str[0] == str[1] == str[2]) {
			Count = 3;
		}
	}
	return Count;
}

int giftSafety(string gift) {
	int Count = 0;
	for (int i = 0; i < gift.length() - 2; ++i) {
		string substr = gift.substr(i, 3);
		Count += sameNum(substr);
	}
	return Count;
}

int main() {
	cout << giftSafety("doll") << endl; // 1
	cout << giftSafety("aaaaaaa") << endl; // 5
}