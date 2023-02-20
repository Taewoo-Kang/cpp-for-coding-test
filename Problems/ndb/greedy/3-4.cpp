// 1이 될 때까지
// 출처: 2018 E 기업 알고리즘 대회

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> condition) {
  int answer = 0;

	int N = condition[0];
	int K = condition[1];

	// while (N != 1) {
	// 	if (N % K) {
	// 		N--;
	// 	} else {
	// 		N /= K;
	// 	}
	// 	answer++;
	// }

	while (N != 1) {
		int next = (N / K) * K;
		answer += (N - next);  // 1씩 빼는 횟수
		N = next;
		N /= K;
		answer++;
	}

  return answer;
}

void print(vector<int> condition, int answer) {
  int result = solution(condition);
  if (result == answer) {
    cout << "Correct!" << endl;
  } else {
    cout << "Wrong Answer" << endl;
    cout << "=> Answer is: " << answer << endl;
    cout << "=> Result is: " << result << endl;
  }
}

int main() {
  print({25, 5}, 2);
  return 0;
}