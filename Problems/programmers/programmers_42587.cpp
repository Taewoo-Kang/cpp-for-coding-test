// 프린터
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42587

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// sort를 하는 대신 priority_queue를 이용할 수도 있음

int solution(vector<int> priorities, int location) {
    vector<int> printOrder(priorities.size());
    queue<pair<int, int>> q;
    for (int i = 0; i < priorities.size(); ++i) {
        q.push(make_pair(priorities[i], i));
    }

    sort(priorities.begin(), priorities.end(), greater<int>());
    auto it = priorities.begin();
    int order = 1;
    while (!q.empty()) {
        int priority = q.front().first;
        int idx = q.front().second;
        q.pop();

        if (priority == *it) {
            printOrder[idx] = order;
            ++it;
            ++order;
        } else {
            q.push(make_pair(priority, idx));
        }
    }

    return printOrder[location];
}

void print(vector<int> priorities, int location, int answer) {
    int result = solution(priorities, location);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({2, 1, 3, 2}, 2, 1);
    print({1, 1, 9, 1, 1, 1}, 0, 5);
    return 0;
}