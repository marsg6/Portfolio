#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/Ky2mjgmxnWLi6KNPp

bool isUnstablePair(string filename1, string filename2) {
	bool firstCase = filename1 < filename2;
	for (auto& c : filename1) { c = toupper(c); }
	for (auto& c : filename2) { c = toupper(c); }
	bool secondCase = filename1 < filename2;
	return firstCase ^ secondCase;
}

int main() {
	cout << isUnstablePair("aa", "AAB") << endl; // true
	cout << isUnstablePair("A", "z") << endl; // false
}