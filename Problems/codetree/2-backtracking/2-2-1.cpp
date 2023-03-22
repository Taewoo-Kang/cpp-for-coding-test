// 특정 조건에 맞게 k개 중에 1개를 n번 뽑기

/**
 * 1이상 K이하의 숫자를 하나 고르는 행위를 N번 반복하여 나올 수 있는 모든 서로 다른 순서쌍
 * 단, 연속하여 같은 숫자가 3번 이상 나오는 경우는 제외
*/

#include <iostream>
#include <vector>

using namespace std;

int K;
int N;
vector<int> selected;

void recursion() {
  if (selected.size() == N) {
    for (int i = 0; i < N; ++i) {
      cout << selected[i] << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = 1; i <= K; ++i) {
    int len = selected.size();
    if (len >= 2 && selected[len - 1] == i && selected[len - 2] == i) {
      continue;
    }
    selected.push_back(i);
    recursion();
    selected.pop_back();
  }
}

void init() {
  selected.clear();
}

void solution() {
  init();

  cin >> K >> N;

  recursion();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  freopen("2-2-1.input", "r", stdin);
  freopen("2-2-1.output", "w", stdout);
  for (int i = 0; i < 2; ++i) {
    solution();
  }

  return 0;
}