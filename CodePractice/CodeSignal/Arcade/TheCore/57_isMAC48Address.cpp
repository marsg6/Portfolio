#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/HJ2thsvjL25iCvvdm

bool isMAC48Address(string inputString) {
	if (inputString.size() != 17) { return false; }

	for (int i = 0; i < inputString.size(); ++i) {
		auto c = inputString[i];
		if (i % 3 == 2) {
			if (c != '-') {
				return false;
			}
		}
		else {
			if (c < '0' || ('9' < c && c < 'A') || 'F' < c) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	cout << isMAC48Address("00-1B-63-84-45-E6") << endl; // true
	cout << isMAC48Address("Z1-1B-63-84-45-E6") << endl; // false
}