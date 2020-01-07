#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Search(int X, int Y, vector<vector<char>>& Map, size_t& Count) {
	if (Map[Y][X] == '0') {
		return;
	}
	else {
		++Count;
		Map[Y][X] = '0';
	}

	if (0 <= X - 1)				Search(X - 1, Y, Map, Count);
	if (X + 1 < Map[0].size())	Search(X + 1, Y, Map, Count);
	if (0 <= Y - 1)				Search(X, Y - 1, Map, Count);
	if (Y + 1 < Map.size())		Search(X, Y + 1, Map, Count);
}

int main() {
	int N;
	cin >> N;
	
	vector<vector<char>> Map;
	for (int y = 0; y < N; ++y) {
		vector<char> Row;
		for (int x = 0; x < N; ++x) {
			char Input;
			cin >> Input;
			
			Row.push_back(Input);
		}
		Map.push_back(Row);
	}

	vector<size_t> Sections;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (Map[y][x] == '1') {
				size_t ApartCount = 0;
				Search(x, y, Map, ApartCount);
				Sections.push_back(ApartCount);
			}
		}
	}

	sort(Sections.begin(), Sections.end());
	cout << Sections.size() << endl;
	for (auto Count : Sections) {
		cout << Count << endl;
	}
}