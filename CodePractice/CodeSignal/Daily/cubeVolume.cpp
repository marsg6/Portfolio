#include <iostream>

using namespace std;

int cubeVolume(int n) {
	return pow(n, 3);
}

int main() {
	cout << cubeVolume(5) << endl; // 125
	cout << cubeVolume(1) << endl; // 1
}
