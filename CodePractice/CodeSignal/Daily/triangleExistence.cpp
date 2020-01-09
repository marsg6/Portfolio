#include <iostream>
#include <vector>

using namespace std;

// https://app.codesignal.com/challenge/4nwZHgbjAXTquopxR

bool triangleExistence(vector<int> sides) {
	for (int first = 0; first < 3; ++first) {
		int second = (first + 1) % 3;
		int other = (second + 1) % 3;
		/* To be a triangle, the sum of any two sides should be larger than the other side. */
		if (sides[first] + sides[second] <= sides[other]) {
			return false;
		}
	}
	return true;
}

int main() {
	cout << (triangleExistence({ 1, 2, 10 }) ? "true" : "false") << endl;
	cout << (triangleExistence({ 6, 2, 5 }) ? "true" : "false") << endl;
}