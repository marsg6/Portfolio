#include <iostream>
#include <vector>
#include <string>

using namespace std;

//https://app.codesignal.com/challenge/bSbiYfA43DLCabtoZ

bool correctNonogram(int size, vector<vector<string>> nonogramField) {
	int start = (size + 1) / 2;
	for (int i = start; i < nonogramField.size(); ++i) {
		string currNum = to_string(nonogramField.size() - start);
		int currIndex = 0;
		for (int j = 0; j < start; ++j) {
			if (nonogramField[i][j] != "-") {
				currNum = nonogramField[i][j];
				currIndex = j;
				break;
			}
		}
		auto prevStr = nonogramField[i][start];
		for (int j = start; j < nonogramField.size(); ++j) {
			if (nonogramField[i][j] == prevStr) {
				--currNum[0];
				if (currNum == "0") {
					currNum = nonogramField[i][++currIndex];
				}
			}
		}
	}
}

int main() {

}