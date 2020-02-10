#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/2SDWWyHY9Xw5CpphY

bool isTandemRepeat(string inputString) {
	string halfStr = inputString.substr(0, inputString.size() / 2);
	return halfStr + halfStr == inputString;
}

int main() {
	cout << isTandemRepeat("tandemtandem") << endl; // true
	cout << isTandemRepeat("qqq") << endl;			// false
}