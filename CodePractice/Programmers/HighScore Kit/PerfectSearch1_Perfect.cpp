#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;

    vector<int> counts(3, 0);

    vector<int> seconds{ 1, 3, 4, 5 };
    vector<int> thirds{ 3,1,2,4,5 };

    for (int i = 0; i < answers.size(); ++i) {
        int first = i % 5 + 1;
        int second = i % 2 ? seconds[(i / 2) % 4] : 2;
        int third = thirds[(i / 2) % 5];

        if (answers[i] == first) ++counts[0];
        if (answers[i] == second) ++counts[1];
        if (answers[i] == third) ++counts[2];
    }
    int maxVal = max({ counts[0], counts[1], counts[2]});
    for (int i = 0; i < counts.size(); ++i) {
        if (maxVal == counts[i]) {
            answer.emplace_back(i + 1);
        }
    }
    return answer;
}