#include <iostream>
#include <string>

using namespace std;

//https://app.codesignal.com/challenge/wdaNioTdYMMogFHeH

int higherVersion2(string ver1, string ver2) {
	int f1 = stoi(ver1), f2 = stoi(ver2);
	int s1 = stoi(ver1.substr(ver1.find('.') + 1)), s2 = stoi(ver2.substr(ver2.find('.') + 1));
	int t1 = stoi(ver1.substr(ver1.find_last_of('.') + 1)), t2 = stoi(ver2.substr(ver2.find_last_of('.') + 1));
	return f1 < f2 ? -1 : f1 > f2 ? 1 : s1 < s2 ? -1 : s1 > s2 ? 1 : t1 < t2 ? -1 : t1 > t2 ? 1 : 0;
}

int main() {
	cout << higherVersion2("1.2.2", "1.2.0") << endl; // 1
	cout << higherVersion2("1.0.5", "1.1.0") << endl; // -1
}