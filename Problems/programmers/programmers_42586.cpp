// 기능개발
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42586

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> q;
    for (int progress : progresses) {
        q.push(progress);
    }

    int taskIdx = 0;
    int dayCnt = 0;
    while (!q.empty()) {
        int taskCnt = 0;
        for ( ; taskIdx < progresses.size(); ++taskIdx) {
            if (q.front() + speeds[taskIdx] * dayCnt < 100) {
                break;
            }
            q.pop();
            ++taskCnt;
        }

        if (taskCnt) {
            answer.push_back(taskCnt);
        }
        ++dayCnt;
    }

    return answer;
}

void print(vector<int> progresses, vector<int> speeds, vector<int> answer) {
    vector<int> result = solution(progresses, speeds);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({93, 30, 55}, {1, 30, 5}, {2, 1});
    print({95, 90, 99, 99, 80, 99}, {1, 1, 1, 1, 1, 1}, {1, 3, 2});
    return 0;
}