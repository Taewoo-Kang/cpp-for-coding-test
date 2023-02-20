// 숫자 카드 게임
// 출처: 2019 국가 교육기관 코딩테스트

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> condition, vector<vector<int>> numbers) {
  int answer = 0;

	for (vector<int> row : numbers) {
		sort(row.begin(), row.end());
		answer = row[0] > answer ? row[0] : answer;
	}

  return answer;
}

void print(vector<int> condition, vector<vector<int>> numbers, int answer) {
  int result = solution(condition, numbers);
  if (result == answer) {
    cout << "Correct!" << endl;
  } else {
    cout << "Wrong Answer" << endl;
    cout << "=> Answer is: " << answer << endl;
    cout << "=> Result is: " << result << endl;
  }
}

int main() {
  print({3, 3}, {{3, 1, 2}, {4, 1, 4}, {2, 2, 2}}, 2);
  print({2, 4}, {{7, 3, 1, 8}, {3, 3, 3, 4}}, 3);
  return 0;
}