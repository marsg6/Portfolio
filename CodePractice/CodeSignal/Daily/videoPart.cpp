#include <iostream>
#include <string>
#include <vector>

using namespace std;

//https://app.codesignal.com/challenge/aesrryCpibT2mevy6

int gcd(int a, int b) {
	int c = 0;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

vector<int> videoPart(string part, string total) {
	int p = stoi(part.substr(0, 2)) * 3600 + stoi(part.substr(3, 2)) * 60 + stoi(part.substr(6, 2));
	int t = stoi(total.substr(0, 2)) * 3600 + stoi(total.substr(3, 2)) * 60 + stoi(total.substr(6, 2));
	
	int g = gcd(t, p);
	return { p / g, t / g};
}

int main() {
	cout << videoPart("02:20:00", "07:00:00")[0] << ", " << videoPart("02:20:00", "07:00:00")[1] << endl; // { 1, 3 }
	cout << videoPart("25:26:20", "25:26:20")[0] << ", " << videoPart("25:26:20", "25:26:20")[1] << endl; // { 1, 1 }
}