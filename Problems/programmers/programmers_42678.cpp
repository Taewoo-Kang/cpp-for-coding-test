// 이중우선순위큐
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42628

#include <iostream>
#include <iterator> // for ostream_iterator
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

// 참고! multiset을 사용할 경우 중복 허용 및 정렬 가능
// multiset을 활용한 풀이는 밑에 주석처리하여 첨부

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    priority_queue<int> pq;
    priority_queue<int, vector<int>, greater<int>> rpq;

    int cnt = 0;
    for (string operation : operations) {
        if (operation[0] == 'I') {
            int num = stoi(operation.substr(2));
            pq.push(num);
            rpq.push(num);
            ++cnt;
        } else if (operation[0] == 'D') {
            if (cnt == 0) {
                continue;
            }
            if (operation[2] == '-') {
                rpq.pop();
            } else {
                pq.pop();
            }
            --cnt;
        }

        if (cnt == 0) {
            pq = priority_queue<int>();
            rpq = priority_queue<int, vector<int>, greater<int>>();
        }
    }

    if (cnt == 0) {
        answer.push_back(0);
        answer.push_back(0);
    } else {
        answer.push_back(pq.top());
        answer.push_back(rpq.top());
    }
    return answer;
}
/*
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    multiset<int> ms;
    
    for(auto o : operations){
        if(o == "D 1" && ms.size()>0){
            ms.erase(--ms.end());
        }else if(o == "D -1" && ms.size()>0){
            ms.erase(ms.begin());
        }else if(o[0] == 'I'){
            ms.insert(stoi(o.substr(2, o.size()-2)));
        }
    }
    if(ms.size() == 0)
        return {0, 0};
    else
        return {*(--ms.end()), *ms.begin()};
}
*/
template <typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
  if ( !v.empty() ) {
    os << '[';
    copy(v.begin(), --v.end(), ostream_iterator<T>(os, ", "));
    os << v.back() << ']';
  }
  return os;
}

void print(vector<string> operations, vector<int> answer) {
    vector<int> result = solution(operations);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print({"I 16", "D 1"}, {0, 0});
    print({"I 7", "I 5", "I -5", "D -1"}, {7, 5});
    print({"I 4", "I 3", "I 2", "I 1", "D 1", "D 1", "D -1", "D -1", "I 5", "I 6"}, {6,5});
    return 0;
}