// k개 중에 1개를 n번 뽑기

/**
 * 1이상 K이하의 숫자를 하나 고르는 행위를 N번 반복하여 나올 수 있는 모든 서로 다른 순서쌍
 * 
 * 입력:
 * 1 <= K <= 4
 * 1 <= N <= 8
 * 
 * 출력:
 * 한 줄에 하나씩 순서쌍 상태를 공백을 사이에 두고 출력
 * 앞에서부터 봤을 때 사전순으로 앞선 순서쌍부터
*/

#include <iostream>
#include <vector>

using namespace std;

int K, N;
vector<int> vec;

void recursion(int count) {
  if (count == N) {
    for (int elem : vec) {
      cout << elem << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = 1; i <= K; ++i) {
    vec.push_back(i);
    recursion(count + 1);
    vec.pop_back();
  }
}

void solution() {
  cin >> K >> N;

  vec.reserve(N);
  recursion(0);
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-1-1.input", "r", stdin);
  freopen("2-1-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}