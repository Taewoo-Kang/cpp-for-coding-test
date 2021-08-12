// 위장
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42578

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map<string, int> clothMap;
    for (auto cloth : clothes) {
        ++clothMap[cloth[1]];
    }

    for (auto it = clothMap.begin(); it != clothMap.end(); ++it) {
        answer *= it->second + 1;
    }
    return answer - 1;
}

void print(vector<vector<string>> clothes, int answer) {
    int result = solution(clothes);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({{"yellowhat", "headgear"}, {"bluesunglasses", "eyewear"}, {"green_turban", "headgear"}}, 5);
    print({{"crowmask", "face"}, {"bluesunglasses", "face"}, {"smoky_makeup", "face"}}, 3);
    return 0;
}