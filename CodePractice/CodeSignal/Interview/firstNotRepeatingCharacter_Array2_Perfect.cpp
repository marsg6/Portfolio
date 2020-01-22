#include <iostream>
#include <string>
#include <vector>

using namespace std;

char firstNotRepeatingCharacter(string s) {
	vector<int> alphabets(26, 0);
	for (const auto& c : s) {
		++alphabets[c - 'a'];
	}
	for (const auto& c : s) {
		if (alphabets[c - 'a'] == 1) {
			return c;
		}
	}
	return '_';
}


int main() {
	cout << firstNotRepeatingCharacter("abacabad") << endl; // c
	cout << firstNotRepeatingCharacter("abacabaabacaba") << endl; // _
}
