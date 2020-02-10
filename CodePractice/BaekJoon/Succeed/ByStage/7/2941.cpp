#include <iostream>
#include <string>

using namespace std;

int main() {
	string s;
	cin >> s;

	string strs[8] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };

	for (int i = 0; i < 8; ++i) {
		int j = s.find(strs[i]);
		while (j != string::npos) {
			s.replace(j, strs[i].size(), "1");
			j = s.find(strs[i]);
		}
	}

	cout << s.size();
}