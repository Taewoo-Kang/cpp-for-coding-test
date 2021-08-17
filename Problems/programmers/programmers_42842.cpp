// 카펫
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42842

#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int total = brown + yellow;
    int sqrtNum = sqrt(total);
    for (int y = 3; y <= sqrtNum; ++y) {
        if (total % y != 0) {
            continue;
        }
        int x = total / y;
        if (x * 2 + (y-2) * 2 == brown) {
            answer.push_back(x);
            answer.push_back(y);
            break;
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

void print(int brown, int yellow, vector<int> answer) {
    vector<int> result = solution(brown, yellow);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print(10, 2, {4, 3});
    print(8, 1, {3, 3});
    print(24, 24, {8, 6});
    return 0;
}