#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/MX94DWTrwQw2gLrTi

string htmlEndTagByStartTag(string startTag) {
	size_t Index = startTag.find(' ');
	if (Index == -1) {
		Index = startTag.size() - 1;
	}
	return "</" + startTag.substr(1, Index - 1) + ">";
}


int main() {
	cout << htmlEndTagByStartTag("<button type='button' disabled>") << endl; // </button>
	cout << htmlEndTagByStartTag("<i>") << endl; // </i>
}