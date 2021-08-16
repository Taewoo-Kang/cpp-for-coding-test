// 더 맵게
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42626

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// template<class T, class Container, class Compare> class priority_queue
// priority_queue의 정렬 순서를 바꾸기 위해서는 container를 포함해서 선언해야 함

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    // 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두번째로 맵지 않은 음식의 스코빌 지수 * 2)
    while (pq.size() > 1 && pq.top() < K) {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        pq.push(first + second * 2);
        ++answer;
    }

    if (pq.top() < K) {
        answer = -1;
    }

    return answer;
}

void print(vector<int> scoville, int K, int answer) {
    int result = solution(scoville, K);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print({1, 2, 3, 9, 10, 12}, 7, 2);
    print({1, 2, 3, 9, 10, 12}, 100000, -1);
    return 0;
}