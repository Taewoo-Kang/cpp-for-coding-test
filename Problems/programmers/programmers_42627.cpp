// 디스크 컨트롤러
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42627

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using JobType = vector<int>;

struct cmp {
    bool operator()(const JobType &lhs, const JobType &rhs) {
    return lhs[1] > rhs[1];
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    priority_queue<JobType, vector<JobType>, greater<JobType>> startTimes(jobs.begin(), jobs.end());
    priority_queue<JobType, vector<JobType>, cmp> reqJobs;

    int time = 0;
    while (!startTimes.empty() || !reqJobs.empty()) {
        while (!startTimes.empty() && startTimes.top()[0] <= time) {
            reqJobs.push(startTimes.top());
            startTimes.pop();
        }

        if (!reqJobs.empty()) {
            JobType job = reqJobs.top();
            reqJobs.pop();
            time += job[1];
            answer += time - job[0];
        } else {
            time = startTimes.top()[0];
        }
    }
    return answer /= jobs.size();
}

void print(vector<vector<int>> jobs, int answer) {
    int result = solution(jobs);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print({{0,3}, {1,9}, {2,6}}, 9);
    print({{0,1}}, 1);
    print({{1000,1000}}, 1000);
    print({{0,10}, {2,10}, {9,10}, {15,2}}, 14);
    print({{24, 10}, {28, 39}, {43, 20}, {37, 5}, {47, 22}, {20, 47}, {15, 34}, {15, 2}, {35, 43}, {26, 1}}, 72);
    return 0;
}