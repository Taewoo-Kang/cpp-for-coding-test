// 소수 찾기
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42839

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

bool isPrime(int num) {
    if (num == 1)
        return false;
    if (num == 2)
        return true;
    
    int sqrtNum = sqrt(num);
    for (int i = 2; i <= sqrtNum; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

bool checkNum(string str, unordered_map<char, int> charMap) {
    // charMap은 복사되어 전달된 값
    for (char c : str) {
        if (--charMap[c] < 0) {
            return false;
        }
    }
    return true;
}

int solution(string numbers) {
    int answer = 0;
    unordered_map<char, int> charMap;
    for (char c : numbers) {
        ++charMap[c];
    }

    sort(numbers.begin(), numbers.end(), greater<char>());
    int maxValue = stoi(numbers);
    for (int i = 2; i <= maxValue; ++i) {
        if (isPrime(i)) {
            if (checkNum(to_string(i), charMap)) {
                ++answer;
            }
        }
    }
    return answer;
}

void print(string numbers, int answer) {
    int result = solution(numbers);
    if (result == answer)        
        cout << "Correct!" << endl;
    else {
        cout << "Wrong Answer" << endl;
        cout << "=> Answer is: " << answer << endl;
        cout << "=> Result is: " << result << endl;
    }
}
 
int main() {
    print("17", 3);
    print("011", 2);
    return 0;
}