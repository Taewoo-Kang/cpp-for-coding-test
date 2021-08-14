// 가장 큰 수
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42746

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 주의사항:
// 1. string으로 정렬할 경우 3보다 30, 34가 앞으로 감
// 2. 주어진 numbers가 0만 있을 경우 고려 필요

bool cmp(string lhs, string rhs) {
    return lhs + rhs > rhs + lhs;
}

string solution(vector<int> numbers) {
    string answer;
    vector<string> strNumbers;
    for (int number : numbers) {
        strNumbers.push_back(to_string(number));
    }

    sort(strNumbers.begin(), strNumbers.end(), cmp);
    for (string str : strNumbers) {
        answer += str;
    }

    if (answer[0] == '0') {
        return "0";
    }
    return answer;
}

void print(vector<int> numbers, string answer) {
    string result = solution(numbers);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({6, 10, 2}, "6210");
    print({3, 30, 34, 5, 9}, "9534330");
    print({0, 0, 0}, "0");
    return 0;
}