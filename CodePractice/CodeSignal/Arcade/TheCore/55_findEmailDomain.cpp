#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/arcade/code-arcade/book-market/TXFLopNcCNbJLQivP

string findEmailDomain(string address) {
	return address.substr(address.rfind('@') + 1);
}

int main() {
	cout << findEmailDomain("prettyandsimple@example.com") << endl; // example.com
	cout << findEmailDomain("fully-qualified-domain@codesignal.com") << endl; // codesignal.com
}