#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/challenge/AiXeyeX6pB8AvE2p6

string classifyStrings(string s) {
	int vowelCount = 0;
	int consoCount = 0;
	bool isMixed = false;

	for (auto c : s) {
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
			if (vowelCount) {
				++vowelCount;
			}
			else {
				isMixed = false;
				consoCount = 0;
				vowelCount = 1;
			}
		}
		else if (c == '?') {
			if (vowelCount) {
				++vowelCount;
			}
			else if (consoCount) {
				++consoCount;
			}
			else {
				++vowelCount;
				++consoCount;
			}
			isMixed = true;
		}
		else {
			if (consoCount) {
				++consoCount;
			}
			else {
				isMixed = false;
				vowelCount = 0;
				consoCount = 1;
			}
		}

		if (vowelCount == 3 || consoCount == 5) {
			return isMixed ? "mixed" : "bad";
		}
	}
	return "good";
}

int main() {
	cout << "aeu" << endl; // "bad"
	cout << "a?u" << endl; // "mixed"
}