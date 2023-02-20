// 큰 수의 법칙
// 출처: 2019 국가 교육기관 코딩 테스트

/* 문제:
 * 다양한 수로 이루어진 배열이 있을 때 주어진 수들을 M번 더하여 가장 큰 수를 만드는 법칙
 * 단, 배열의 특정한 인덱스에 해당하는 수가 연속으로 K번을 초과하여 더해질 수 없음
 * 서로 다른 인덱스에 해당하는 수가 같은 경우에도 서로 다른 것으로 간주
 *
 * 입력 조건:
 * 첫째 줄에 N(2 <= N <= 1,000), M(1 <= M <= 10,000), K(1 <= K <= 10,000)의 자연수
 * 둘째 줄에 N개의 자연수를 공백으로 구분하여 주어짐(단, 자연수는 1 이상 10,000 이하의 수)
 * K는 항상 M보다 작거나 같다.
 * 
 * 출력 조건:
 * 첫째 줄에 큰 수의 법칙에 따라 더해진 답을 출력
 * */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> condition, vector<int> numbers) {
  int answer = 0;
	int N = condition[0];
	int M = condition[1];
	int K = condition[2];

  sort(numbers.begin(), numbers.end(), greater<>());
  int first = numbers[0];
  int second = numbers[1];

  // int cnt = 0;
  // for (int m = 0; m < M; m++) {
  //   if (cnt < K) {
  //     answer += first;
  //     cnt++;
  //   } else {
  //     answer += second;
  //     cnt = 0;
  //   }
  // }

  int cnt = (M / (K + 1)) * K;
  cnt += M % (K + 1);

  answer = cnt * first + (M - cnt) * second;

  return answer;
}

void print(vector<int> condition, vector<int> numbers, int answer) {
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
  print({5, 8, 3}, {2, 4, 5, 4, 6}, 46);
  return 0;
}