#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/K2ieDm98sPDzzMepz

string encloseInBrackets(string inputString) {
	return '(' + inputString + ')';
}

int main() {
	cout << encloseInBrackets("abacaba") << endl; // (abacaba)
	cout << encloseInBrackets("abcdef") << endl; // (abcdef)
}