#include <iostream>
#include <vector>

using namespace std;

//https://app.codesignal.com/challenge/pxGRg7MAj6yMY9DDp

bool newRoadSystem(vector<vector<bool>> roadRegister) {
	size_t s = roadRegister.size();
	for (int i = 0; i < s; ++i) {
		size_t count = 0;
		for (int j = 0; j < s; ++j) {
			count += roadRegister[i][j] - roadRegister[j][i];
		}
		if (count) { return false; }
	}
	return true;
}

int main() {

}