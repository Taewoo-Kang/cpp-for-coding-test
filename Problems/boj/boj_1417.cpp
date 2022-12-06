// 국회의원 선거
// 출처: https://www.acmicpc.net/problem/1417

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// using PersonVotePair = pair<int, int>;

// struct cmp {
//     bool operator()(const PersonVotePair &lhs, const PersonVotePair &rhs) {
//         return lhs.second < rhs.second ||
//                (lhs.second == rhs.second && lhs.first > rhs.first);
//     }
// };

int solution(vector<int> input) {
    int ret = 0;

    int target = input[1];
    priority_queue<int> pq(input.begin()+2, input.end());

    while (pq.size() && pq.top() >= target) {
        int top = pq.top();
        pq.pop();
        target++;
        pq.push(--top);
        ret++;
    }

    return ret;
}

void print(vector<int> input, int answer) {
    int result = solution(input);
    if (result == answer) {
        cout << "Correct!" << endl;
    } else {
        cout << "Wrong Answer" << endl;
        cout << "Result: " << result << ", Answer: " << answer << endl;
    }
}
 
int main() {
    print({3, 5, 7, 7}, 2);
    print({4, 10, 10, 10, 10}, 1);
    print({1, 1}, 0);
    print({5, 5, 10, 7, 3, 8}, 4);
    return 0;
}