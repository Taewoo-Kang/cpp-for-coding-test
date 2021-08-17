// 모의고사
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42840

#include <iostream>
#include <iterator> // for ostream_iterator
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> score(3);
    vector<vector<int>> supoja({{1,2,3,4,5},
                                {2,1,2,3,2,4,2,5},
                                {3,3,1,1,2,2,4,4,5,5}});

    for (int i = 0; i < answers.size(); ++i) {
        for (int j = 0; j < score.size(); ++j) {
            if (supoja[j][i % supoja[j].size()] == answers[i]) {
                ++score[j];
            }
        }
    }

    vector<int> sortedScore = score;
    sort(sortedScore.begin(), sortedScore.end(), greater<int>());
    int maxValue = sortedScore[0];
    for (int i = 0; i < score.size(); ++i) {
        if (score[i] == maxValue) {
            answer.push_back(i+1);
        }
    }
    return answer;
}

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
  if ( !v.empty() ) {
    os << '[';
    copy(v.begin(), --v.end(), ostream_iterator<T>(os, ", "));
    os << v.back() << ']';
  }
  return os;
}

void print(vector<int> answers, vector<int> answer) {
    vector<int> result = solution(answers);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print({1,2,3,4,5}, {1});
    print({1,3,2,4,2}, {1,2,3});
    return 0;
}