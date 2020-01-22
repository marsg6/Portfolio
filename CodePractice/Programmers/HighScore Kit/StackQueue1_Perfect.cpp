#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> heights) {
    vector<int> answer(heights.size(), 0);
    for (int i = heights.size() - 1; 0 <= i; --i) {
        for (int j = i - 1; 0 <= j; --j) {
            if (heights[i] < heights[j]) {
                answer[i] = j + 1;
                break;
            }
        }
    }
    return answer;
}