#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<int> q;
    for (int i = 0; i < bridge_length - 1; ++i) {
        q.push(0);
    }

    int currWeight = 0;
    int passedTime = 0;

    for (int i = 0; i < truck_weights.size(); ) {
        if (truck_weights[i] <= weight - currWeight) {
            currWeight += truck_weights[i];
            q.push(truck_weights[i]);
            ++i;
        }
        else {
            q.push(0);
        }
        currWeight -= q.front();
        q.pop();
        ++passedTime;
    }

    return passedTime + bridge_length;
}