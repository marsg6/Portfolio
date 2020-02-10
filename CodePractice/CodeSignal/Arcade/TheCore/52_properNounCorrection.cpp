#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/2nSEQ8CGoddTJtnbo

string properNounCorrection(string noun) {
	noun[0] = toupper(noun[0]);
	for (int i = 1; i < noun.size(); ++i) {
		noun[i] = tolower(noun[i]);
	}
	return noun;
}

int main() {
	cout << properNounCorrection("pARiS") << endl; // Paris
	cout << properNounCorrection("mary") << endl; // Mary
}