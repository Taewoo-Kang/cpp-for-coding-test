// 전화번호 목록
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42577

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// TODO: 테스트 케이스는 모두 통과했지만 채점해보면 틀리는 문제가 있음
bool solution(vector<string> phone_book) {
    unordered_set<int> lengthSet;
    for (string phoneNumber : phone_book) {
        lengthSet.insert(phoneNumber.size());
    }

    unordered_map<string, int> phoneMap;
    for (string phoneNumber : phone_book) {
        for (int length : lengthSet) {
            string phoneStr = phoneNumber.substr(0, length);
            ++phoneMap[phoneStr];
        }
    }

    for (auto pair : phoneMap) {
        if (pair.second > 1) {
            return false;
        }
    }

    return true;
}

void print(vector<string> phone_book, bool answer) {
    bool result = solution(phone_book);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({"119", "97674223", "1195524421"}, false);
    print({"123", "456", "789"}, true);
    print({"12", "123", "1235", "567", "88"}, false);
    return 0;
}