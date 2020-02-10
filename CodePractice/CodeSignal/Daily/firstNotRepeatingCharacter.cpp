#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://app.codesignal.com/challenge/jTcYipCF76HyCPDSA

char firstNotRepeatingCharacter(string s) {
	int Counts[26] = { 0, };
	vector<char> List;
	for (auto c : s) {
		++Counts[c - 'a'];
		if (Counts[c - 'a'] == 1) {
			List.push_back(c);
		}
		else if(Counts[c - 'a'] == 2) {
			List.erase(find(List.begin(), List.end(), c));
		}
	}
	return List.size() ? List[0] : '_';
}

int main() {
	cout << firstNotRepeatingCharacter("abacabad") << endl; // "c"
	cout << firstNotRepeatingCharacter("abacabaabacaba") << endl; // "_"
}