#include <iostream>
#include <string>

using namespace std;

int main() {
	string s;
	cin >> s;

	for (char c = 'a'; c <= 'z'; ++c) {
		int f = s.find(c) < s.size() ? s.find(c) : -1;
		cout << f << " ";
	}
}