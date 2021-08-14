// K번째 수
// 출처: https://programmers.co.kr/learn/courses/30/lessons/42748

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for (auto command : commands) {
        vector<int> slice(array.begin() + command[0] - 1, array.begin() + command[1]);
        sort(slice.begin(), slice.end());
        answer.push_back(slice.at(command[2] - 1));
    }
    return answer;
}

void print(vector<int> array, vector<vector<int>> commands, vector<int> answer) {
    vector<int> result = solution(array, commands);
    if (result == answer)        
        cout << "Correct!" << endl;
    else        
        cout << "Wrong Answer" << endl;
}
 
int main() {
    print({1, 5, 2, 6, 3, 7, 4}, {{2, 5, 3}, {4, 4, 1}, {1, 7, 3}}, {5, 6, 3});
    return 0;
}