#include <iostream>
#include <string>

using namespace std;

int main() {
	string s;
	cin >> s;

	int counts[26] = {0,};
	
	bool dup = false;
	char maxC = 0;
	int max = 0;
	for (auto& c : s) {
		c = toupper(c);
		++counts[c - 'A'];


		if (max < counts[c - 'A']) {
			maxC = c;
			max = counts[c - 'A'];
			dup = false;
		}
		else if (counts[c - 'A'] == max) {
			dup = true;
		}
	}

	cout << (dup ? '?' : maxC) << endl;
}