#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq{scoville.begin(), scoville.end()};
    
    int count = 0;
    while (2 <= pq.size() && pq.top() < K) {
        int lowest = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        pq.push(lowest + second * 2);
        
        ++count;
    }
    if (pq.top() < K) count = -1;

    return count;
}