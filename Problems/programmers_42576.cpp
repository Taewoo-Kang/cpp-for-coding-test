// 완주하지 못한 선수
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42576

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 참고! unordered_map의 operator[]에서 key가 없을 경우에는 초기값을 생성하므로 int의 경우 0으로 초기화 됨
// 출처: https://stackoverflow.com/questions/59192236/does-stdunordered-map-operator-do-zero-initialization-for-non-exisiting-key

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> personMap;
    for (string p_person : participant) {
        if (personMap.find(p_person) == personMap.end()) { // 조건 확인 불필요
            personMap.insert(make_pair(p_person, 1));
        } else {
            personMap[p_person]++;
        }
    }

    for (string c_person : completion) {
        if (personMap.find(c_person) != personMap.end()) {
            personMap[c_person]--;
        }
    }

    for (auto pair : personMap) {
        if (pair.second > 0) {
            answer = pair.first;
            break;
        }
    }
    return answer;
}

void print(vector<string> participant, vector<string> completion, string answer) {
    string result = solution(participant, completion);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({"leo", "kiki", "eden"}, {"eden", "kiki"}, "leo");
    print({"marina", "josipa", "nikola", "vinko", "filipa"}, {"josipa", "filipa", "marina", "nikola"}, "vinko");
    print({"mislav", "stanko", "mislav", "ana"}, {"stanko", "ana", "mislav"}, "mislav");
    return 0;
}