#include <iostream>
#include <vector>

using namespace std;

// https://app.codesignal.com/challenge/ddEZp78usMvhQEu3i

int arrayConversion(vector<int> inputArray) {
    for (int i = 0; inputArray.size() != 1; ++i) {
        if (!(i % 2)) {
            for (int j = 0; j < inputArray.size(); ++j) {
                inputArray[j] += inputArray[j + 1];
                /* Erase next element, and then j will indicate the next one of the erased one. */
                inputArray.erase(inputArray.begin() + j + 1);
            }
        }
        else {
            for (int j = 0; j < inputArray.size(); ++j) {
                inputArray[j] *= inputArray[j + 1];
                inputArray.erase(inputArray.begin() + j + 1);
            }
        }
    }
    return inputArray[0];
}


int main() {
	cout << arrayConversion({ 1, 2, 3, 4, 5, 6, 7, 8 }) << endl;
	cout << arrayConversion({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
}