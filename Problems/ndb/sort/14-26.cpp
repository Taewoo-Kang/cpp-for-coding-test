// 카드 정렬하기
// 출처: https://www.acmicpc.net/problem/1715

/**
 * 정렬된 두 묶음의 숫자 카드의 수가 각각 A,B라 하면 합쳐서 하나로 만드는 데 A+B번 비교 필요
 * N개의 숫자 카드 묶음의 각각의 크기가 주어질 때, 최소한 몇 번의 비교가 필요한지
 * 
 * 입력:
 * 첫째 줄에 N이 주어짐(1 <= N <= 100,000)
 * 이어서 N개의 줄에 걸쳐 숫자 카드 묶음의 각각의 크기가 주어짐(0 < 묶음 크기 <= 1,000)
 * 
 * 출력:
 * 첫째 줄에 최소 비교 횟수를 출력
*/

#include <iostream>
#include <queue>

using namespace std;

int N;

void solution() {
  cin >> N;

  priority_queue<int, vector<int>, greater<int>> cards;
  for (int i = 0; i < N; ++i) {
    int num;
    cin >> num;
    cards.push(num);
  }

  int ret = 0;
  while (cards.size() != 1) {
    int cur = cards.top();
    cards.pop();
    int next = cards.top();
    cards.pop();
    ret += (cur + next);
    cards.push(cur + next);
  }

  cout << ret << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("14-26.input", "r", stdin);
  freopen("14-26.output", "w", stdout);
  for (int i = 0; i < 1; ++i) {
    solution();
  }

  return 0;
}
