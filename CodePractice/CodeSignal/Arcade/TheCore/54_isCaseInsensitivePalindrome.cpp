#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/G9wj2j6zaWwFWsise

bool isCaseInsensitivePalindrome(string inputString) {
	for (auto& c : inputString) {
		c = tolower(c);
	}
	for (int i = 0; i < inputString.size() / 2; ++i) {
		if (inputString[i] != inputString[inputString.size() - i - 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	cout << isCaseInsensitivePalindrome("AaBaa") << endl; // true
	cout << isCaseInsensitivePalindrome("abac") << endl; // false
}