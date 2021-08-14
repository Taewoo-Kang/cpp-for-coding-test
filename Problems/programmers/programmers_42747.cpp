// H-Index
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42747

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    sort(citations.begin(), citations.end(), greater<int>());
    if (citations[0] == 0) {
        return 0;
    }

    for (int i = 0; i < citations.size(); i++) {
        if (citations[i] <= i) {
            break;
        }
        ++answer;
    }
    return answer;
}

void print(vector<int> citations, int answer) {
    int result = solution(citations);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({3, 0, 6, 1, 5}, 3);
    print({0, 1, 1}, 1);
    print({0, 0, 0}, 0);
    return 0;
}